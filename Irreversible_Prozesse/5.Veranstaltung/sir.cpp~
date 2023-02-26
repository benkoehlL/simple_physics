#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <set>

#include <SDL.h>
#include <SDL_gfxPrimitives.h>

#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_cdf.h>

using namespace std;

int seed=14;
  gsl_rng *rng;
  
/*	Definition of a node within a small world network
*/
class SmallWorldNode {
	private:
		int nodenum;		// Node number
		vector<double> pos;	// Node position on unit circle
		int n;				// number of neighbors
		set<int> neighbors;	// node numbers of neighbors
		
	public :
		double ps;
		double pi;
		double pr;
		
		SmallWorldNode(int n_) : 
			nodenum(0), pos(2, 0.), n(n_), neighbors() {}

/* setting the correct neighborhood
*/		
		void initial(double initialpinfect, double initialprecover,double initialpsusceptible)
		{
		  ps=initialpsusceptible;
		  pr=initialprecover;
		  pi=initialpinfect;
		}

		void set_neighbors(vector<double> pos_, set<int> neighbors_, int num_) {			
			pos.clear();
			pos = pos_;
			neighbors.clear();
			neighbors = neighbors_;
			nodenum = num_;
		}
		
/* replace/ add/ remove a given edge
*/
		void set_rewireEdge(int jold, int jnew) {
			neighbors.erase(jold);
			neighbors.insert(jnew);
		}
		
		void set_addEdge(int jnew) {
			neighbors.insert(jnew);
			++n;
		}
		void set_removeEdge(int jold) {
			neighbors.erase(jold);
			--n;
		}
		
		vector<double> get_pos () const {
			return pos;
		} 
		
		set<int> get_neighbors () const {
			return neighbors;
		}
		
/*	find a random new available neighbor 
*/		
		int get_randomNode(gsl_rng *rng, int v) {
			int index;
			bool impossible = true;
			while (impossible) {
				index = gsl_rng_uniform_int(rng,v);
				if( (index != nodenum) && 
					(neighbors.find(index) == neighbors.end()) ) {
					impossible = false;
					return index;
				}
			 }
			 return index;
		}

		int get_numneigh() const {
			return n;
		}
		
		double get_numps() const {
			return ps;
		}
		
		double get_numpi() const {
			return pi;
		}
		
		double get_numpr() const {
			return pr;
		}
		
		void print_SmallWorldNode() const {
			set<int>::iterator it;
			cout << nodenum << " (" << pos[0] << ", " << pos[1] << ") ";
			cout << '\t';
			for (it=neighbors.begin(); it!=neighbors.end(); ++it) {
				cout << ' ' << *it;
			}
			cout << '\n';
		}
		
		void step (
		
};

/*	Definition of small world network
*/
class SmallWorld {
	private: 
		int v, nreg; 	// number of vertices and neighbors per vertex
		vector<SmallWorldNode> nodes;	// nodes within the network
	public :
		SmallWorld (int v_, int n_): 
			v(v_), nreg(n_), nodes(v_, SmallWorldNode(n_)) {}

/*	Initialisation of a regular Small World network (circle)
*/			
		void set_SmallWorld_Regular() {

			for (int i=0; i<v; i++) {
				set<int> neighbors;
				vector<double> pos(2,0.);
				for (int j=0; j<nreg/2; j++) {
					neighbors.insert((i+v-(j+1)) % v);
					neighbors.insert((i+j+1) % v);
				}
				pos[0] = sin(i*2.*M_PI/v);
				pos[1] = cos(i*2.*M_PI/v);
				nodes[i].set_neighbors(pos, neighbors, i);
			}
		}

/*	Rewire the regular small world with prob. p
*/				
		void rewire_SmallWorld(gsl_rng *rng, double p) {
			// randomize at first the nearest neighbors and than second nearest ...
			for(int j=0; j<nreg/2; j++) {
				// go through network
				for (int i=0; i<v; i++) {
					// rewire left neighbor of regular network
					if( gsl_rng_uniform(rng) < p || 1. == p ) {
						int in = (i+j+1) % v;
						int inew = nodes[i].get_randomNode(rng, v);
						nodes[i].set_rewireEdge(in,inew);
						nodes[inew].set_addEdge(i);
						nodes[in].set_removeEdge(i);
					}
				}
			}
		}
		
/*	Drawing small world network via SDL 
*/
		


		void initialall(int N,double pinfect,double precover) {
		  for(int i=0;i<N;i++)
		  {
		    nodes[i].initial(pinfect,precover);
		  }
		}
		void draw_SmallWorld(SDL_Surface *s) {

			boxColor(s, 0,0, s->w,s->h, 0xFFFFFFFF);

	/* Key-Press-Information  */			
			stringColor(s, 10, 10, "Press r: Rewire", 0x000000FF);
			stringColor(s, 10, 20, "Press p: Print node information",
	0x000000FF);
			stringColor(s, 10, 30, "Press o: Print smallworld.dat", 
	0x000000FF);
			stringColor(s, 10, 30, "Press q: next time step", 
	0x000000FF);
			for (int i=0; i<v; i++) {
				vector<double> posn = nodes[i].get_pos();
				int posnx = (posn[0])*s->w/2.5 + s->w/2;
				int posny = (-1*posn[1])*s->h/2.5 + s->h/2;
	/*	Drawing neighborhood  */
	// Hinweis: Die "dünnen" und "dicken" Linien hängen nicht mit
	//		mit der doppelt-Zeichnung von Linien sondern mit dem
	//		Anstieg der Linie zusammen!
				set<int> neighbors = nodes[i].get_neighbors();
				set<int>::iterator it;
				for (it=neighbors.begin(); it!=neighbors.end();it++) {
					vector<double> posj = nodes[(*it)].get_pos();
					int posjx = (posj[0])*s->w/2.5 + s->w/2;
					int posjy = (-1*posj[1])*s->h/2.5 + s->h/2;
					aalineColor(s, posnx, posny, posjx, posjy, 0x000000FF); 
				}
			}
	/*	Drawing the nodes  */
			for (int i=0; i<v; i++) 
			{
				vector<double> posn = nodes[i].get_pos();
				int posnx = (posn[0])*s->w/2.5 + s->w/2;
				int posny = (-1*posn[1])*s->h/2.5 + s->h/2;		
				int offx;
				if(i<10) offx=3; else offx=7;
				stringstream ss; ss << i;
				filledCircleColor(s, posnx, posny, 10, 0x0AFF0AFF);
				stringColor(s, posnx-offx, posny-3, ss.str().c_str(), 0x000000FF);
				if(nodes[i].gesundheitbefore==sus)
				{
				  circleColor(s, posnx, posny, 10, 0x000000FF);
				}
				else
				{
				  circleColor(s, posnx, posny, 10, 0x000FF000);
				}
			SDL_UpdateRect(s, 0,0, s->w,s->h);
			}
		}
		void print_SmallWorld_Dot() const {
/* Darstellung: 
	"circo -Tpdf smallworld.dat > smallworld.pdf" in Konsole eingeben
*/
			ofstream fout;
			fout.open("smallworld.dat");
			fout << "graph g {" << endl;
			fout << "node [style = filled]" << endl;
		// Definition Knotenfarbe
			for (int i=0; i<v; i++) {
				fout << i << " [color=green];" << endl;
			}
		// Ausgabe aller Verbindungen
			for (int i=0; i<v; i++) {
				set<int> neighbors = nodes[i].get_neighbors();
				set<int>::iterator it;
				for (it=neighbors.begin(); it!=neighbors.end(); it++) {
					if (*it > i) {
						fout << i << " -- " << *it << endl;
					}
				}
			}
			fout << "}" << endl;
			fout.close();
		}
		
		void print_SmallWorld () const {
			for (int i=0; i<v; i++) {
				nodes[i].print_SmallWorldNode();
			}
		}
		
		void infect(int N,double pinf,prec,n) 
		{  
		  double suminfect=0;
		  for(int i;i<nodes[n].get_numneig();i++)
		  {
		    suminfect=suminfect+nodes[nodes[n].get_neighbors()[i]].ps;
		  }
		  double sus = nodes[n].get_numps * ( 1 - pinf/nodes[n].get_numneig() * suminfect );
		  double rec = nodes[n].get_numpr + nodes[n].get_numpr * prec;
		  double inf = nodes[n].get_numpi + nodes.get_numps * pinf / nodes[n].get_numneig() * suminfect;
		  nodes[n].initial(inf,rec,sus);
		}
		  
		  
		
};


int main(){
	int N,K,tmax;
	double p,pinfect,precover;
	cout << "Geben Sie die Anzahl der Knoten ein." << '\n';
	cin >> N;
	cout << "Geben Sie  die Anzahl der Verbindungen pro Knoten ein." << '\n';
	cin >> K;
	cout << "Geben Sie die Wahrscheinlichkeit eines Neuvernetzungsvorgangs ein." << '\n';
	cin >> p;
	cout << "Geben Sie die Infektionswahrscheinlichkeit ein." << '\n';
	cin >> pinfect;
	cout << "Geben Sie die Immunisierungswahrscheinlichkeit ein." << '\n';
	cin >> precover;
	cout << "Geben Sie maximale Betrachtungszeit ein." << '\n';
	cin >> tmax;
	
	SmallWorld own(N,K);
	
	own.nodes[0].initial(1,0,0);
	for(int i=1;i<N;i++)
	{
	  own.nodes[i].initial(0,0,1)
	}
	for(int t=1;t<tmax;t++)
	{
	  for(int n=0;n<N,n++)
	  {
	    own.infect(N,pinfect,precover,n);
	  }
	  own.print();
	}
	SDL_Surface *screen;
	SDL_Event event;
	int quit = 0;
	
/* Initialises the video
*/
	if ( -1 == SDL_Init(SDL_INIT_VIDEO ) ) {
		cerr << "Kann Video nicht initialisieren: " << SDL_GetError() << endl;
		return EXIT_FAILURE;
	}
	atexit(SDL_Quit);
	
/* Initialises the screen
*/
	screen = SDL_SetVideoMode(1000, 1000, 16, SDL_HWSURFACE);
	if ( 0 == screen ) {
		cerr << "Kann Video-Modus nicht festlegen: " << SDL_GetError() << endl;
		return EXIT_FAILURE;
	}
	atexit(SDL_Quit);

/* Sets title-bar and icon name of display window
*/
	SDL_WM_SetCaption("Small World Network", "Small World Network");

	rng = gsl_rng_alloc(gsl_rng_mt19937);	// Allocation of Mersenne Twister
	gsl_rng_set(rng,seed);					// Initialisation of MT

	own.set_SmallWorld_Regular();
	
	while (!quit) {
		while (SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_QUIT: 
					quit = 1;
					break;
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {
						case SDLK_ESCAPE:
							quit = 1;
							break;
						case SDLK_r:
							own.set_SmallWorld_Regular();
							own.rewire_SmallWorld(rng, p);
							break;
						case SDLK_p:
							own.print_SmallWorld();
							break;
						case SDLK_o:
							own.print_SmallWorld_Dot();
							break;
						case SDLK_q:
							own.infect(N,pinf);
							t++;
							break;
						default:
							break;
					}
				break;
			}
		}
		boxColor(screen, 0,0, screen->w, screen->h, 0xFFFFFFFF);
		own.draw_SmallWorld(screen);
		SDL_UpdateRect(screen, 0,0, screen->w, screen->h);
	}

	return 0;
}
