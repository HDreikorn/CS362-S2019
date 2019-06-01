CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

testAdventurerRefactor: unittest1.c dominion.o rngs.o
	gcc -o testAdventurerRefactor -g unittest1.c dominion.o rngs.o $(CFLAGS)

testSmithyRefactor: unittest2.c dominion.o rngs.o
	gcc -o testSmithyRefactor -g unittest2.c dominion.o rngs.o $(CFLAGS)

testGreatHallRefactor: unittest3.c dominion.o rngs.o
	gcc -o testGreatHallRefactor -g unittest3.c dominion.o rngs.o $(CFLAGS)

testVillageRefactor: unittest4.c dominion.o rngs.o
	gcc -o testVillageRefactor -g unittest4.c dominion.o rngs.o $(CFLAGS)

testCard1: cardtest1.c dominion.o rngs.o
	gcc -o testCard1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)

testCard2: cardtest2.c dominion.o rngs.o
	gcc -o testCard2 -g cardtest2.c dominion.o rngs.o $(CFLAGS)

testCard3: cardtest3.c dominion.o rngs.o
	gcc -o testCard3 -g cardtest3.c dominion.o rngs.o $(CFLAGS)

testCard4: cardtest4.c dominion.o rngs.o
	gcc -o testCard4 -g cardtest4.c dominion.o rngs.o $(CFLAGS)

unittestresults: testAdventurerRefactor testSmithyRefactor testGreatHallRefactor testVillageRefactor testCard1 testCard2 testCard3 testCard4 dominion.o rngs.o
	echo "unittest1.c" > unittestresults.out
	./testAdventurerRefactor >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	echo "unittest2.c" >> unittestresults.out
	./testSmithyRefactor >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	echo "unittest3.c" >> unittestresults.out
	./testGreatHallRefactor >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	echo "unittest4.c" >> unittestresults.out
	./testVillageRefactor >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	echo "cardtest1.c" >> unittestresults.out
	./testCard1 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	echo "cardtest2.c" >> unittestresults.out
	./testCard2 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	echo "cardtest3.c" >> unittestresults.out
	./testCard3 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	echo "cardtest4.c" >> unittestresults.out
	./testCard4 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out

testAdventurer: randomtestadventurer.c dominion.o rngs.o
	gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o $(CFLAGS)

testGreatHall: randomtestcard1.c dominion.o rngs.o
	gcc -o randomtestcard1 -g  randomtestcard1.c dominion.o rngs.o $(CFLAGS)

testSalvager: randomtestcard2.c dominion.o rngs.o
	gcc -o randomtestcard2 -g randomtestcard2.c dominion.o rngs.o $(CFLAGS)

randomtestresults: testAdventurer testGreatHall testSalvager
	./randomtestadventurer > randomtestresults.out
	gcov dominion.c -fb >> randomtestresults.out
	./randomtestcard1 >> randomtestresults.out
	gcov dominion.c -fb >> randomtestresults.out
	./randomtestcard2 >> randomtestresults.out
	gcov dominion.c -fb >> randomtestresults.out
	cat dominion.c.gcov >> randomtestresults.out

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
