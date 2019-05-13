#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int checkAdventurerAction(int p, struct gameState *post) {
  int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
  struct gameState pre;
  memcpy (&pre, post, sizeof(struct gameState));

  int r;
  //  printf ("drawCard PRE: p %d HC %d DeC %d DiC %d\n",
  //	  p, pre.handCount[p], pre.deckCount[p], pre.discardCount[p]);
    
  r = cardEffect(adventurer, choice1, choice2, choice3, post, handpos, &bonus);

  //printf ("drawCard POST: p %d HC %d DeC %d DiC %d\n",
  //      p, post->handCount[p], post->deckCount[p], post->discardCount[p]);

//   if (pre.deckCount[p] > 0) {
//     pre.handCount[p] += 2;
//     pre.hand[p][pre.handCount[p]-1] = pre.deck[p][pre.deckCount[p]-1];
//     pre.deckCount[p]--;
//   } else if (pre.discardCount[p] > 0) {
//     memcpy(pre.deck[p], post->deck[p], sizeof(int) * pre.discardCount[p]);
//     memcpy(pre.discard[p], post->discard[p], sizeof(int)*pre.discardCount[p]);
//     pre.hand[p][post->handCount[p]-1] = post->hand[p][post->handCount[p]-1];
//     pre.handCount[p]++;
//     pre.deckCount[p] = pre.discardCount[p]-1;
//     pre.discardCount[p] = 0;
//   }

  assert (r == 0);

  assert(pre.handCount[p]+=2 == post->handCount[p]);
}

int main () {

  int i, n, r, p, j, deckCount, discardCount, handCount;

  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

  struct gameState G;

  printf ("Testing adventurerAction.\n");

  printf ("RANDOM TESTS.\n");

  SelectStream(2);
  PutSeed(3);

  for (n = 0; n < 2000; n++) {
    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&G)[i] = floor(Random() * 256);
    }
    p = floor(Random() * 2);
    G.deckCount[p] = floor(Random() * MAX_DECK);
    G.discardCount[p] = floor(Random() * MAX_DECK);
    G.handCount[p] = floor(Random() * MAX_HAND);
    //Randomize deck
    for(j=0; j<G.deckCount[p]; j++){
        G.deck[p][j] = floor(Random() * treasure_map);
    }
    checkAdventurerAction(p, &G);
  }
return 0;
}