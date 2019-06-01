#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>
#include <time.h>

void checkAdventurerAction(int p, struct gameState *post) {
  int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
  struct gameState pre;
  memcpy (&pre, post, sizeof(struct gameState));

  int r;
    //printf ("drawCard PRE: p %d HC %d DeC %d DiC %d\n",
  	  //p, pre.handCount[p], pre.deckCount[p], pre.discardCount[p]);
  
  r = cardEffect(adventurer, choice1, choice2, choice3, post, handpos, &bonus);

  	//printf ("drawCard POST: p %d HC %d DeC %d DiC %d\n",
        //p, post->handCount[p], post->deckCount[p], post->discardCount[p]);

  assert (r == 0);
  assert(pre.handCount[p]+=2 == post->handCount[p]);
}

int main () {

  int n, p, j, seed =1;

  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

  struct gameState G;

  printf ("Testing adventurerAction.\n");

  printf ("RANDOM TESTS.\n");

  SelectStream(2);
  PutSeed(time(NULL));
  initializeGame(2, k, seed, &G);

  for (n = 0; n < 2000; n++) {
	  p = 0;
	  G.whoseTurn = 0;
    G.deckCount[p] = floor(Random() * MAX_DECK);
    G.discardCount[p] = floor(Random() * MAX_DECK);
    G.handCount[p] = floor(Random() * MAX_HAND);
    //Randomize deck
    for(j=0; j<G.deckCount[p]; j++){
        G.deck[p][j] = floor(Random() * treasure_map);
    }
    checkAdventurerAction(p, &G);
  }
  printf("Tests complete.\n");
return 0;
}