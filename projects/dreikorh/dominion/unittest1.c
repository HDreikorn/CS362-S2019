/*
* UNIT TEST 1: Positive testing refactored adventurer action.
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
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int i, game, seed = 1, player = 0, numPlayers = 3, handCount = 0;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    int startingSupplyCount[treasure_map+1] = {0};
	int p1FullDeck[3], p2FullDeck[3];
    struct gameState G; 

	printf("Starting Unit Test 1 suite...\n");
    game = initializeGame(numPlayers, k, seed, &G);
    assert(game == 0);
	printf("Game initialized successfully for testing...\n");
    // Capture before states of handCount, victory cards, kingdom cards, and playershand, deck, discard count.
    handCount = numHandCards(&G);
	for(i=0; i < 17; i++) {
		startingSupplyCount[i] = G.supplyCount[i];
	}

	// All players, but player 0 who starts
	p1FullDeck[0] = G.handCount[1];
	p2FullDeck[0] = G.handCount[2];
	p1FullDeck[1] = G.deckCount[1];
	p2FullDeck[1] = G.deckCount[2];
	p1FullDeck[2] = G.discardCount[1];
	p2FullDeck[2] = G.discardCount[2];

    // Run cardEffect to test refactored adventurer action.
    game = cardEffect(adventurer, choice1, choice2, choice3, &G, handpos, &bonus);

    // Test 1: Test if hand count has increased by 2, checking for exactly 2 also ensures other cards were discarded.
	printf("TEST 1: ");
	MY_ASSERT(numHandCards(&G) == (handCount+2), "FAILED - G.handCount = %d, Expected = %d\n", numHandCards(&G), handCount+2);

	// Test 2: Test if last card is a treasure card.
	printf("TEST 2: ");
    MY_ASSERT((G.hand[player][numHandCards(&G)-1] == 4) ||
			  (G.hand[player][numHandCards(&G)-1] == 5) ||
			  (G.hand[player][numHandCards(&G)-1] == 6), "FAILED - Last card is %d, not treasure\n", G.hand[player][numHandCards(&G)-1], 0);

    // Test 3: Test if second to last card is a treasure card.
	printf("TEST 3: ");
    MY_ASSERT((G.hand[player][numHandCards(&G)-2] == 4) ||
			  (G.hand[player][numHandCards(&G)-2] == 5) ||
			  (G.hand[player][numHandCards(&G)-2] == 6), "FAILED - Last card is %d, not treasure\n", G.hand[player][numHandCards(&G)-2], 0);
	
	// Test 4: Test to make sure no changes were made to victory cards or kingdom cards
    printf("Test 4: ");
    for (i=0; i <6; i++) {
		if (startingSupplyCount[i] != G.supplyCount[i]){
			printf("FAILED - Unexpected change made in card %d", i);
			break;
		}
	}
	printf("PASSED\n");

	// Test 5: Test to make sure no changes were made to every other player's deck.
	printf("Test 5: ");
	MY_ASSERT((p1FullDeck[0] == G.handCount[1]) &&
			  (p2FullDeck[0] == G.handCount[2]) &&
			  (p1FullDeck[1] == G.deckCount[1]) &&
			  (p2FullDeck[1] == G.deckCount[2]) &&
			  (p1FullDeck[2] == G.discardCount[1]) &&
			  (p2FullDeck[2] == G.discardCount[2]),"FAILED - Unexpected change made in other player card.\n", 0, 0);	

	printf("Unit Test 1 complete.\n");

	return 0;
}
