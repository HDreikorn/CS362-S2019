#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>
#include <time.h>

void checkGreatHallAction(int p, struct gameState *post, int handpos) {
  int choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
  struct gameState pre;
  memcpy (&pre, post, sizeof(struct gameState));

  int r;
    printf ("great hall PRE: HC %d HP %d Action %d\n", pre.handCount[p], handpos, pre.numActions);
  
  r = cardEffect(great_hall, choice1, choice2, choice3, post, handpos, &bonus);

  	printf ("great hall POST: HC %d HP %d Action %d\n", post->handCount[p], handpos, post->numActions);

  assert (r == 0);
  //assert(pre.handCount[p]+=1 == post->handCount[p]);
  //assert(pre.numActions +=1 == post->numActions);
}

int main () {

  int n, p, j, trashFlag, seed =1, handpos = 0;

  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

  struct gameState G;

  printf ("Testing greatHallAction.\n");

  printf ("RANDOM TESTS.\n");

  SelectStream(2);
  PutSeed(time(NULL));
  initializeGame(2, k, seed, &G);

  for (n = 0; n < 2000; n++) {
    G.deckCount[p] = floor(Random() * MAX_DECK);
    G.discardCount[p] = floor(Random() * MAX_DECK);
    G.handCount[p] = floor(Random() * MAX_HAND);
    //Randomize deck
    for(j=0; j<G.deckCount[p]; j++){
        G.deck[p][j] = floor(Random() * treasure_map);
    }
    handpos = floor(Random() * G.handCount[p]);
    checkGreatHallAction(p, &G, handpos);
  }
  printf("Tests complete.\n");
return 0;
}
