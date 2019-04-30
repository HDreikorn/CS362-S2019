/*
* CARD TEST 1: Boundry testing Adventurer.
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
	
	printf("Starting Boundry Adventurer test suite...\n");
    game = initializeGame(numPlayers, k, seed, &G);
	printf("Game initialized successfully for testing...\n");
	assert(game == 0);
    // Init last card in deck to be non treasure.
    G.deck[ player ][ G.deckCount[player] ] = smithy;
    G.deckCount[player]++;
    for (i=0; i<G.deckCount[player]; i++) {
        printf("Deck before: %d", G.deck[player][i]);
    }

    // Run card effect to test adventurer funtion.
    game = cardEffect(adventurer, choice1, choice2, choice3, &G, handpos, &bonus);

    // Test cards are discarded when first draws are not treasures.
    for (i=0; i<G.deckCount[player]; i++) {
        printf("Deck after: %d", G.deck[player][i]);
    }
    for (i=0; i<G.discardCount[player]; i++) {
        printf("Discard: %d", G.discard[player][i]);
    }
	
	return 0;
}
