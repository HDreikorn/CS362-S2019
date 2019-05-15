#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>
#include <time.h>

int checkSalvagerAction(int p, struct gameState *post, int handpos, int choice1) {
  int choice2 = 0, choice3 = 0, bonus = 0;
  struct gameState pre;
  memcpy (&pre, post, sizeof(struct gameState));

  int r;
  //printf ("Salvager PRE: BUYS %d Choice1 %d Coins %d\n", pre.numBuys, choice1, pre.coins);
  if (choice1 == 0) {
	printf("Choice card: %d, pre buys: %d post pre card effect buys: %d\n", pre.hand[p][choice1], pre.numBuys, post->numBuys);
  }		  
  r = cardEffect(salvager, choice1, choice2, choice3, post, handpos, &bonus);
  
  //printf ("Salvager POST: BUYS %d Choice1 %d Coins %d\n", post->numBuys, choice1, post->coins);

  pre.numBuys++;

  if (choice1) {
	//printf("Choice card: %d\n", pre.hand[p][choice1]);
	pre.coins = getCost(pre.hand[p][choice1]);
  }

  assert (r == 0);
  if(pre.numBuys != post->numBuys) {
	printf("FAIL BUYS - pre: %d, post: %d, choice1: %d, pre HC: %d, post HC: %d\n", pre.numBuys, post->numBuys, choice1, pre.handCount[p], post->handCount[p]);
	return 1;
  }
  if (pre.coins != post->coins) {
	printf("FAIL COINS- pre: %d, post: %d\n", pre.coins, post->coins);
	return 1;
  }
  return 0;
}

int main () {

  int n, p, j, seed =1, handpos = 0, choice1 = 0, fail = 0;

  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

  struct gameState G;

  printf ("Testing Salvager Action.\n");

  printf ("RANDOM TESTS.\n");

  SelectStream(2);
  PutSeed(time(NULL));
  initializeGame(2, k, seed, &G);
  p = 0;

  for (n = 0; n < 2000; n++) {
    G.numBuys = 1;
	G.coins = 0;
    G.deckCount[p] = floor(Random() * MAX_DECK);
    G.discardCount[p] = floor(Random() * MAX_DECK);
    G.handCount[p] = floor(Random() * MAX_HAND);
    //Randomize hand
    for(j=0; j<G.handCount[p]; j++){
        G.hand[p][j] = floor(Random() * treasure_map);
    }
    handpos = floor(Random() * G.handCount[p]);
    choice1 = floor(Random() * G.handCount[p]);
    fail += checkSalvagerAction(p, &G, handpos, choice1);
  }
  printf("Tests complete.FAILS: %d\n", fail);
return 0;
}
