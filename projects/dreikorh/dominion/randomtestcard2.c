#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>
#include <time.h>

void checkSalvagerAction(int p, struct gameState *post, int handpos, int choice1) {
  int choice2 = 0, choice3 = 0, bonus = 0;
  struct gameState pre;
  memcpy (&pre, post, sizeof(struct gameState));

  int r;
  //printf ("great hall PRE: HC %d HP %d Action %d\n", pre.handCount[p], handpos, pre.numActions);
  
  r = cardEffect(salvager, choice1, choice2, choice3, post, handpos, &bonus);

  //printf ("great hall POST: HC %d HP %d Action %d\n", post->handCount[p], handpos, post->numActions);
  pre.numBuys++;

  assert (r == 0);
  assert(pre.numBuys == post->numBuys);
}

int main () {

  int n, p, j, trashFlag, seed =1, handpos = 0, choice1 = 0;

  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

  struct gameState G;

  printf ("Testing Salvager Action.\n");

  printf ("RANDOM TESTS.\n");

  SelectStream(2);
  PutSeed(time(NULL));
  initializeGame(2, k, seed, &G);

  for (n = 0; n < 2000; n++) {
    G.numBuys = 1;
    G.deckCount[p] = floor(Random() * MAX_DECK);
    G.discardCount[p] = floor(Random() * MAX_DECK);
    G.handCount[p] = floor(Random() * MAX_HAND);
    //Randomize hand
    for(j=0; j<G.handCount[p]; j++){
        G.hand[p][j] = floor(Random() * treasure_map);
    }
    handpos = floor(Random() * G.handCount[p]);
    choice1 = floor(Random() * G.handCount[p]);
    checkSalvagerAction(p, &G, handpos, choice1);
  }
  printf("Tests complete.\n");
return 0;
}
