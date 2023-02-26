CFLAGS=-O3 -pedantic `sdl-config --cflags`
LDFLAGS=`sdl-config --libs` -lSDL_gfx

CC=g++
LD=g++

%.o: %.cpp
	$(CC) -c $(CFLAGS) $<
ALL: Hiddenmarkov Viterbi Backward

Hiddenmarkov: Hiddenmarkov.o
	    $(LD) -o  Hiddenmarkov Hiddenmarkov.o -lgsl -lgslcblas -lm $(LDFLAGS)

Viterbi: Viterbi.o
	    $(LD) -o  Viterbi Viterbi.o -lgsl -lgslcblas -lm $(LDFLAGS)

Backward: Backward.o
	    $(LD) -o  Backward Backward.o -lgsl -lgslcblas -lm $(LDFLAGS)
