/*
* CARD TEST 4: Postive testing for sea hag card.
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
    int game, seed = 1, player = 0, numPlayers = 3;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int p1TopCard, p2TopCard, p1DeckCount, p2DeckCount;
	
	printf("Starting positive Salvager tests...\n");
    game = initializeGame(numPlayers, k, seed, &G);
	printf("Game initialized successfully for testing...\n");
	assert(game == 0);

    // Capture before states
    p1TopCard = G.deck[1][G.deckCount[1]];
    p1DeckCount = G.deckCount[1];
    p2TopCard = G.deck[2][G.deckCount[2]];
    p2DeckCount = G.deckCount[2];
    
    // Run the function set to salvager card action
    game = cardEffect(sea_hag, choice1, choice2, choice3, &G, handpos, &bonus);

    // Test 1: All other players discarded top card of deck
    printf("Test 1.a: ");
    MY_ASSERT(G.discard[1][0] == p1TopCard, "FAIL - G.discard[1][0] = %d, Expected = %d\n", G.discard[1][0], p1TopCard);
    printf("Test 1.b: ");
    MY_ASSERT(G.discard[2][0] == p2TopCard, "FAIL - G.discard[2][0] = %d, Expected = %d\n", G.discard[2][0], p2TopCard);

    // Test 2: All players gain a Curse card on thier top deck
    printf("Test 2.a: ");
    MY_ASSERT(G.deck[1][p1DeckCount-1] == curse, "FAIL - P1 top deck card = %d, Expected = %d\n", G.deck[1][p1DeckCount-1], curse);
    printf("Test 2.b: ");
    MY_ASSERT(G.deck[2][p2DeckCount-1] == curse, "FAIL - P2 top deck card = %d, Expected = %d\n", G.deck[2][p2DeckCount-1], curse);

    // Test 3: Deck count remains the same
    printf("Test 3.a: ");
    MY_ASSERT(G.deckCount[1] == p1DeckCount, "FAIL - P1 deckCount = %d, Expected = %d\n", G.deckCount[1], p1DeckCount);
    printf("Test 3.b: ");
    MY_ASSERT(G.deckCount[2] == p2DeckCount, "FAIL - P2 top deck card = %d, Expected = %d\n", G.deckCount[2], p2DeckCount);

    // Test 4: Player 0 did not discard top of thier deck
    printf("Test 4: ");
    MY_ASSERT(G.discardCount[player] == 0, "FAIL - G.discardCount[0] = %d, Expected = %d\n", G.discardCount[player], 0);

    // Test 5: Player 0 did not get a curse card on top of their deck
    printf("Test 5: ");
    MY_ASSERT(G.deck[player][G.deckCount[player]-1] != curse, "FAIL - p0 top deck card = %d, Expected = %s\n", G.deck[player][G.deckCount[player]-1], "treasure (4,5, or 6)");

	printf("Card Test 4 complete.\n");

	return 0;
}
