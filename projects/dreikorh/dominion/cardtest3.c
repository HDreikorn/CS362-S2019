/*
* CARD TEST 3: Postive testing for salvager card.
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define MY_ASSERT(condition, msg, arg1, arg2)\
	if (condition)\
		printf("PASSED\n"); \
	else \
		printf(msg, arg1, arg2);

int main() {
    int handpos = 0, choice1 = 1, choice2 = 0, choice3 = 0, bonus = 0;
    int i, game, seed = 1, player = 0, numPlayers = 3, numBuys = 0, coins = 0;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int startingSupplyCount[treasure_map+1] = {0};
	int p1FullDeck[3], p2FullDeck[3]; 
	
	printf("Starting positive Salvager tests...\n");
    game = initializeGame(numPlayers, k, seed, &G);
	printf("Game initialized successfully for testing...\n");
	assert(game == 0);

    // Capture before states
    numBuys = G.numBuys;
    coins = G.coins;
    G.hand[player][1] = village;

    // Capture starting supply state
    for(i=0; i < 17; i++) {
		startingSupplyCount[i] = G.supplyCount[i];
	}

	// Caputre full deck state for all players, but player 0 who starts
	p1FullDeck[0] = G.handCount[1];
	p2FullDeck[0] = G.handCount[2];
	p1FullDeck[1] = G.deckCount[1];
	p2FullDeck[1] = G.deckCount[2];
	p1FullDeck[2] = G.discardCount[1];
	p2FullDeck[2] = G.discardCount[2];

    // Run the function set to salvager card action
    game = cardEffect(salvager, choice1, choice2, choice3, &G, handpos, &bonus);

    // Test 1: The buy count is increased by 1
    printf("Test 1: ");
    MY_ASSERT((numBuys+1 == G.numBuys), "Failed - G.numBuys = %d, Expected = %d\n", G.numBuys, numBuys+1);

    // Test 2: Card is trashed from hand, not in played or discard
    printf("Test 2.a: ");
    MY_ASSERT(G.playedCardCount == 1, "Failed - G.playedCardCount = %d, Expected = %d\n", G.playedCardCount, 1);
    printf("Test 2.b: ");
    MY_ASSERT(G.discardCount[player] == 0, "Failed - G.discardCount = %d, Expected = %d\n", G.discardCount[player], 0);

    // Test 3: Get +3 coins for trashing village
    printf("Test 3: ");
    MY_ASSERT(G.coins == coins+3, "Failed - G.coins = %d, Expected = %d\n", G.coins, coins+3);
    // Test 4: No state change for supply cards
    printf("Test 4: ");
    for (i=0; i <6; i++) {
		if (startingSupplyCount[i] != G.supplyCount[i]){
			printf("FAILED - Unexpected change made in card %d", i);
			break;
		}
	}
	printf("PASSED\n");

    // Test 5: No state change for other players cards
    printf("Test 5: ");
    MY_ASSERT((p1FullDeck[0] == G.handCount[1]) &&
			  (p2FullDeck[0] == G.handCount[2]) &&
			  (p1FullDeck[1] == G.deckCount[1]) &&
			  (p2FullDeck[1] == G.deckCount[2]) &&
			  (p1FullDeck[2] == G.discardCount[1]) &&
			  (p2FullDeck[2] == G.discardCount[2]),"FAILED - Unexpected change made in other player card; player %d or %d\n", 1, 2);	

	printf("Card Test 3 complete.\n");

	return 0;
}
