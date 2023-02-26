CC=g++
LD=g++
CFLAGS=-O3 -pedantic

%.o: %.cpp parameter.h
	$(CC) -c $(CFLAGS) $<

ALL: diffusion idiffusion

diffusion: diffusion.o
	    $(LD) $(LDFLAGS) -o diffusion diffusion.o -lgsl -lgslcblas -lm
idiffusion: idiffusion.o
	    $(LD) $(LDFLAGS) -o idiffusion idiffusion.o -lgsl -lgslcblas -lm

run:
	./diffusion
