/*
* UNIT TEST 2: Positive testing refactored smithyAction.
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define MY_ASSERT(condition, msg)\
	if (condition)\
		printf("PASSED\n"); \
	else \
		printf(msg);

int main() {
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int game, deckCount, seed = 1, player = 0, numPlayers = 4, handCount = 0;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G; 
	
	printf("Starting Unit Test 2 suite...\n");
    game = initializeGame(numPlayers, k, seed, &G);
	printf("Game initialized successfully for testing...\n");
	assert(game == 0);
    handCount = numHandCards(&G);
	deckCount = G.deckCount[player];
    game = cardEffect(adventurer, choice1, choice2, choice3, &G, handpos, &bonus);

    // Test 1: Test if hand count has increased by 3.
	printf("TEST 1: ");
	if(handCount == (handCount+3))
		printf("PASSED\n");
	else
		printf("FAILED - G.handCount = %d, Expected = %d\n", numHandCards(&G), handCount+3);

	// Test 2: Test if cards came from own pile.
	printf("TEST 2: ");
    if((deckCount-3) == G.deckCount[player])
		printf("PASSED");
	else
		printf("FAILED - G.deckCount = %d, Expected = %d\n", G.deckCount[player], deckCount-3);
	return 0;
}
