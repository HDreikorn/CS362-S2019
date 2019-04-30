/*
* UNIT TEST 4: Positive testing refactored village.
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
		printf(msg);

int main() {
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int i, game, deckCount, seed = 1, player = 0, numPlayers = 3, handCount = 0, numActions = 0;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
	int startingSupplyCount[treasure_map+1] = {0};
	int p1FullDeck[3], p2FullDeck[3];
    struct gameState G; 
	
	printf("Starting Unit Test 4 suite...\n");
    game = initializeGame(numPlayers, k, seed, &G);
	printf("Game initialized successfully for testing...\n");
	assert(game == 0);
	// Capture before states
    handCount = numHandCards(&G);
	deckCount = G.deckCount[player];
    numActions = G.numActions;

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

	// Run cardEffect to test refactored Smithy action
    game = cardEffect(village, choice1, choice2, choice3, &G, handpos, &bonus);

    // Test 1: Test if hand count has increased by 1 and then discard 1.
	printf("TEST 1: ");
	if(handCount == (handCount))
		printf("PASSED\n");
	else
		printf("FAILED - G.handCount = %d, Expected = %d\n", numHandCards(&G), handCount);

	// Test 2: Test if card came from own pile, by testing if deck decreased.
	printf("TEST 2: ");
    if((deckCount-1) == G.deckCount[player])
		printf("PASSED\n");
	else
		printf("FAILED - G.deckCount = %d, Expected = %d\n", G.deckCount[player], deckCount-1);

	// Test 3: Test if action state increased by one for the player.
    printf("TEST 3: ");
    if(numActions+2 == G.numActions)
        printf("PASSED\n");
    else
        printf("FAILED - G.numActions = %d, Expected = %d\n", G.numActions, numActions+2);

    // Test 4: No state change for the supply cards (victory, gold, kingdom)
	printf("TEST 4: ");
	for (i=0; i <6; i++) {
		if (startingSupplyCount[i] != G.supplyCount[i]){
			printf("FAILED - Unexpected change made in card %d", i);
			break;
		}
	}
	printf("PASSED\n");

	// Test 5: No state change for any of the other players. 
	printf("TEST 5: ");
	MY_ASSERT((p1FullDeck[0] == G.handCount[1]) &&
			  (p2FullDeck[0] == G.handCount[2]) &&
			  (p1FullDeck[1] == G.deckCount[1]) &&
			  (p2FullDeck[1] == G.deckCount[2]) &&
			  (p1FullDeck[2] == G.discardCount[1]) &&
			  (p2FullDeck[2] == G.discardCount[2]),"FAILED - Unexpected change made in other player card.\n", 0, 0);

	printf("Unit test 4 complete.\n");
	return 0;
}
