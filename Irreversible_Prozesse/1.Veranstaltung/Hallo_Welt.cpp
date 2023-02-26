#include <iostream>
#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <cstdlib>
#include <cmath>
// http://www.ferzkopp.net/Software/SDL_gfx-2.0/Docs/html/index.html

double x;
double y;
double a;
double b;
double epsilon;


int main(int argc, char const *argv[])
{
	x=0;
	y=0;
	epsilon=0.01;
	
	SDL_Surface *screen;
	SDL_Event event;
	int quit = 0;

	if (SDL_Init(SDL_INIT_VIDEO) == -1) {
		std::cerr << "Kann Video nicht initialisieren: " << SDL_GetError() << std::endl;
		return EXIT_FAILURE;
	}

	atexit(SDL_Quit);

	screen = SDL_SetVideoMode(1024, 768, 16, SDL_HWSURFACE);
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
	  
	  y=500+400*sin(x);
	  boxColor(screen,0,0,1024,768,0x000000FF);
	  filledCircleColor(screen,250,y,25,0xFF00FFFF);
	  SDL_Flip(screen);
	  x=x+0.01;
	}

	return EXIT_SUCCESS;
}
