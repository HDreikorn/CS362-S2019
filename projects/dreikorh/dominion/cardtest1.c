/*
* CARD TEST 1: Boundry testing discarded cards for Adventurer.
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define MY_ASSERT(condition, msg, arg1, arg2, arg3)\
	if (condition)\
		printf("PASSED\n"); \
	else \
		printf(msg, arg1, arg2, arg3);

int main() {
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int i, game, seed = 1, player = 0, numPlayers = 3 ;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G; 
	
	printf("Starting Boundry Adventurer test suite...\n");
    game = initializeGame(numPlayers, k, seed, &G);
	printf("Game initialized successfully for testing...\n");
	assert(game == 0);
    // Insert adventuer card in hand.
    G.hand[player][ G.handCount[player] - 1 ] = adventurer;

    //**********************************************************************
    // TEST 1: No card is discarded when first 2 cards in deck are treasures.
    //**********************************************************************
    // Init first 2 cards to be treasure.
    G.deck[ player ][ G.deckCount[player] ] = copper;
    G.deckCount[player]++;
    G.deck[ player ][ G.deckCount[player] ] = gold;
    G.deckCount[player]++;
    // Run card effect to test adventurer funtion.
    game = cardEffect(adventurer, choice1, choice2, choice3, &G, handpos, &bonus);
    printf("Test 1: ");
    MY_ASSERT((G.discardCount[player] == 0), "FAILED - G.discardCount[player] = %d, Expected = %d. %s", G.discardCount[player], 0, "Unexpected card discarded.\n");

    //*************************************************************
    // Test 2: Test if adventurer was discarded into playedCards.
    //*************************************************************
    printf("Test 2: ");
    MY_ASSERT((G.playedCardCount == 1), "FAILED - G.playedCardCount = %d, Expected = %d. %s", G.playedCardCount, 1, "Played card was not discarded.\n");

    //*************************************************************
    // TEST 3: Card is discarded when first draw is not a treasure.
    //*************************************************************
    // Init last card in deck to be non treasure.
    G.deck[ player ][ G.deckCount[player] ] = smithy;
    G.deckCount[player]++;

    // Run card effect to test adventurer funtion.
    game = cardEffect(adventurer, choice1, choice2, choice3, &G, handpos, &bonus);

    printf("Test 3: ");
    MY_ASSERT((G.discard[player][0] == smithy), "FAILED - G.discard[player][0] = %d, Expected = %d. %s", G.discard[player][0], smithy, "Wrong card discarded.\n");

    //********************************************************************
    // TEST 4: 10 Cards are discared when first 10 cards are not treasure
    //********************************************************************
    
    // Init last 10 cards to not be treasure
    for (i=0; i<10; i++) {
        G.deck[player][G.deckCount[player]] = smithy;
        G.deckCount[player]++;
    }
    
	// Run card effect to test adventurer funtion.
    game = cardEffect(adventurer, choice1, choice2, choice3, &G, handpos, &bonus);

    printf("Test 4: ");
    for (i=3; i<13; i++) {
        if(G.discard[player][i] != smithy) {
            printf("FAILED - G.discard[player][%d] = %d, Expected = %d\n", i, G.discard[player][i], smithy);
			break;
		}
    }
	printf("PASSED\n");

	return 0;
}
