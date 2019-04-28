/*
* UNIT TEST 2: testing refactored cardEffect.
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
    int game, seed = 1, player = 0, numPlayers = 4, handCount = 0;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G; 

    game = initializeGame(numPlayers, k, seed, &G);
	assert(game == 0);
    handCount = numHandCards(&G);
    game = cardEffect(adventurer, choice1, choice2, choice3, &G, handpos, &bonus);

    // Test 1: Test if hand count has increased by 2, checking for exactly 2 also ensures other cards were discarded.
	printf("TEST 1: ");
	MY_ASSERT(numHandCards(&G) == (handCount+2), "\"FAILED: G.handCount = %d, Expected = %d\n\", numHandCards(&G), handCount+2");

	// Test 2: Test if last card is a treasure card.
	printf("TEST 2: ");
    MY_ASSERT((G.hand[player][numHandCards(&G)-1] == 4) ||
			  (G.hand[player][numHandCards(&G)-1] == 5) ||
			  (G.hand[player][numHandCards(&G)-1] == 6), "\"FAILED - Last card is %d, not treasure\",G.hand[player][numHandCards(&G)-1]");
	return 0;
}
