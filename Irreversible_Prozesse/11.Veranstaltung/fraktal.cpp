#include <iostream>

#include <SDL.h>
#include <SDL_gfxPrimitives.h>

#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_cdf.h>
#include <cmath>

#define L 5
using namespace std;

int check(int,int,int[L*L]);

int main()
{
  int generator[L*L];
  int x,y;
  for (int i=0;i<L;i++){
    for (int j=0;j<L;j++){
      cout << "Geben Sie die "<< "(" << i << "," << j << ")-Komponente des Generators ein:" << '\n';
      cin >> generator[i*L+j];
    }
  }
  SDL_Surface *screen;
	SDL_Event event;
	int quit = 0;

	if (SDL_Init(SDL_INIT_VIDEO) == -1) {
		std::cerr << "Kann Video nicht initialisieren: " << SDL_GetError() << std::endl;
		return EXIT_FAILURE;
	}

	atexit(SDL_Quit);

	screen = SDL_SetVideoMode(729, 729, 16, SDL_HWSURFACE);
	if (screen == NULL) {
		std::cerr << "Kann Video-Modus nicht festlegen: " << SDL_GetError() << std::endl;
		return EXIT_FAILURE;
	}

	while (!quit) {
	  while(SDL_PollEvent(&event))
	  {
	  	switch(event.type) {
			case SDL_QUIT:
				quit = 1;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
					case SDLK_ESCAPE:
						quit = 1;
						break;
				}
				break;
		}
	    
	  }
	  for(int x=0;x<729;x++){
		for(int y=0;y<729;y++){
		  if(check(x,y,generator)){
		    pixelRGBA(screen, x, 729-y,0,255,0,255);
		}
	      }
	    }
	  SDL_UpdateRect(screen,0,0,screen-> w,screen -> h);
	}
	return 0;

}

int check(int x,int y,int *generator)
{
  int it,i,j;
  if(x > y) {
    it= static_cast <int>(log(x)/log(L));
  }
  else {
    it= static_cast <int>(log(y)/log(L));
  }
  
  while(it >= 0){
   i= static_cast <int> (x/(pow(L,it))) % L;
    j= static_cast <int> (y/(pow(L,it))) % L;
    if(generator[i*L+j] == 0) {
    return 0;
    }
    if (generator[i*L+j] > 0) {
      it--;
//      check(i,j,generator);

    }
  }
  return 1;
}