CFLAGS=-O3 -pedantic `sdl-config --cflags`
LDFLAGS=`sdl-config --libs` -lSDL_gfx

CC=g++
LD=g++

%.o: %.c
	$(CC) -c $(CFLAGS) $<
ALL: bifurkation Rössler Lorenz Tamari Henon Chua Lotka

bifurkation: bifurkation.o
	    $(LD) -o  bifurkation bifurkation.o -lgsl -lgslcblas -lm $(LDFLAGS)

Rössler: Rössler.o
	    $(LD) -o  Rössler Rössler.o -lgsl -lgslcblas -lm $(LDFLAGS)

Lorenz: Lorenz.o
	    $(LD) -o  Lorenz Lorenz.o -lgsl -lgslcblas -lm $(LDFLAGS)

Tamari: Tamari.o
	    $(LD) -o  Tamari Tamari.o -lgsl -lgslcblas -lm $(LDFLAGS)
Henon: Henon.o
	    $(LD) -o  Henon Henon.o -lgsl -lgslcblas -lm $(LDFLAGS)

Chua: Chua.o
	    $(LD) -o  Chua Chua.o -lgsl -lgslcblas -lm $(LDFLAGS)
Lotka: Lotka.o
	    $(LD) -o  Lotka Lotka.o -lgsl -lgslcblas -lm $(LDFLAGS)

