/*
* UNIT TEST 1: testing refactored adventurer action.
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() {
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int game, seed = 1000, player = 0, numPlayers = 2, handCount = 0;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G; 

    game = initializeGame(numPlayers, k, seed, &G);
    handCount = numHandCards(&G);
    //cardEffect(adventurer, choice1, choice2, choice3, &G, handpos, &bonus);

    // Test 1: Test if hand count has increased by 2.
    //printf("G.handCount = %d, Expected = %d\n", numHandCards(&G), handCount+2);


    return 0;
}