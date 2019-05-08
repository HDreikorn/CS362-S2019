CFLAGS = -Wall -fpic -coverage -lm -std=c99

default: testme

testme: testme.c testme.o
	gcc -o testme testme.c $(CFLAGS)
	-./testme
	gcov testme.c -b

clean:
	-rm  testme testme.c.gcov testme.gcda testme.gcno testme.o
