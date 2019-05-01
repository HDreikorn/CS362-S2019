/*
* CARD TEST 2: Boundry testing handpos for Smithy.
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
    int i, game, seed = 1, player = 0, numPlayers = 3 ;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G; 
	
	printf("Starting Boundry Smithy test suite...\n");
    game = initializeGame(numPlayers, k, seed, &G);
	printf("Game initialized successfully for testing...\n");
	assert(game == 0);
    // Insert smithy card in hand.
    G.hand[player][handpos] = smithy;
    // Set handCount to 1 for consistency
    G.handCount[player] = 1;

    //**********************************************************************
    // TEST 1: Minimum handpos = 0, see if it gets properly placed in played cards.
    //**********************************************************************
    
    // Run card effect to test adventurer funtion.
    game = cardEffect(smithy, choice1, choice2, choice3, &G, handpos, &bonus);
    printf("Test 1: ");
    MY_ASSERT((G.playedCards[player] == smithy), "FAILED - G.playedCards[player] = %d, Expected = %d.\n", G.playedCards[player], smithy);

	return 0;
}
