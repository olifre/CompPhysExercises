#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <SDL/SDL.h>

#define N 350
#define J 1

#define WIDTH 700
#define HEIGHT 700
#define BPP 4
#define DEPTH 32

void put_pixel32( SDL_Surface *surface, int x, int y, Uint32 pixel ) { 
  //Convert the pixels to 32 bit 
  Uint32 *pixels = (Uint32 *)surface->pixels; 
  //Set the pixel 
  pixels[ ( y * surface->w ) + x ] = pixel; 
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination ) { 
  //Make a temporary rectangle to hold the offsets 
  SDL_Rect offset; 
  //Give the offsets to the rectangle 
  offset.x = x; offset.y = y; 
  //Blit the surface 
  SDL_BlitSurface( source, NULL, destination, &offset ); 
} 

double hamiltonian(double lattice[N][N]) {
  double sum=0;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      //sum+=2*lattice[i][j]*lattice[(i+1)%N][j];
      //sum+=2*lattice[i][j]*lattice[i][(j+1)%N];
      //sum+=lattice[i][j]*lattice[(i-1+N)%N][j];
      //sum+=lattice[i][j]*lattice[i][(j-1+N)%N];
      sum+=cos(lattice[i][j]-lattice[(i+1)%N][j]);
      sum+=cos(lattice[i][j]-lattice[i][(j+1)%N]);
      sum+=cos(lattice[i][j]-lattice[(i-1)%N][j]);
      sum+=cos(lattice[i][j]-lattice[i][(j-1)%N]);
    }
  }
  return -1./2.*J*sum;
}

int printLattice(double lattice[N][N]) {
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j)	{
      //std::cout << ((lattice[i][j] == 1) ? "+" : "-") << " ";
      std::cout << ((lattice[i][j] == 1) ? "\033[0;35mU\033[0m" : "\033[0;34mD\033[0m") << " ";
      //std::cout << ((lattice[i][j] == 1) ? "+" : "-") << " ";
    }
    std::cout << std::endl;
  }
  std::cout << "Energy: " << hamiltonian(lattice) << std::endl;;
}

int SDLdrawLattice(double lattice[N][N], SDL_Surface *paintme, SDL_Surface *screen) {

  double scaling = 255./2.;

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j)	{
      for (int k = 0; k < HEIGHT/N; ++k) {
	for (int l = 0; l < WIDTH/N; ++l) {
	  Uint32 pix = SDL_MapRGB( screen->format, 0, 1.+cos(lattice[i][j])*scaling, 0 ); 
	  put_pixel32( paintme, i*HEIGHT/N+k, j*WIDTH/N+l, pix );
	}
      }
    }
    //std::cout << std::endl;
  }
  apply_surface( 0, 0, paintme, screen ); 
  SDL_Flip( screen );
  //SDL_Delay( 10 ); 
}

int randLattice(double lattice[N][N]) {
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j)	{
      lattice[i][j]=(2.*M_PI*random())/(RAND_MAX+1.);
    }
  }
}

int turnSpinR(double lattice[N][N], double *T, int k) {
  int i=(N*1.0*random()/(RAND_MAX+1.));
  int j=(N*1.0*random()/(RAND_MAX+1.));

  //double oldHam=hamiltonian(lattice);
  double newHam;
  double HamPartO, HamPartN, deltaH;
  double oldAngle;
  oldAngle=lattice[i][j];      
  lattice[i][j]=(2.*M_PI*random())/(RAND_MAX+1.);
  
  HamPartO=cos(oldAngle-lattice[(i+1)%N][j]);
  HamPartO+=cos(oldAngle-lattice[i][(j+1)%N]);
  HamPartO+=cos(oldAngle-lattice[(i-1+N)%N][j]);
  HamPartO+=cos(oldAngle-lattice[i][(j-1+N)%N]);
  // Bidirectional = 2.*
  // HamPartO*=2.;
  
  HamPartN=cos(lattice[i][j]-lattice[(i+1)%N][j]);
  HamPartN+=cos(lattice[i][j]-lattice[i][(j+1)%N]);
  HamPartN+=cos(lattice[i][j]-lattice[(i-1+N)%N][j]);
  HamPartN+=cos(lattice[i][j]-lattice[i][(j-1+N)%N]);
  // Bidirectional = 2.*
  // HamPartN*=2.;
  
  deltaH=2.*(HamPartN-HamPartO);
  
  //newHam=hamiltonian(lattice);
  //deltaH=newHam-deltaH;
  double p=std::min(1.,exp(deltaH / (*T)));
  //std::cout << "p=" << p << std::endl;
  if ((1.0*random()/(RAND_MAX+1.)) <= p) {
    //std::cout << deltaH << "\t" << exp(-deltaH / (*T)) << std::endl;
    //std::cout << "Taken." << std::endl;
    //std::cout << "Flipped, Delta H: " << deltaH << std::endl;
    (*T)=1/log(k);
    //deltaH=newHam;
  } else {
    //std::cout << "Not taken." << std::endl;[i][j]=oldAngle;
    lattice[i][j]=oldAngle;
    //deltaH=oldHam;
  }
}

int turnSpinS(double lattice[N][N], double *T, int k) {
  //int i=(N*1.0*random()/(RAND_MAX+1.));
  //int j=(N*1.0*random()/(RAND_MAX+1.));
  //double oldHam=hamiltonian(lattice);
  double newHam;
  double HamPartO, HamPartN, deltaH;
  double oldAngle;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      oldAngle=lattice[i][j];      
      lattice[i][j]=(2.*M_PI*random())/(RAND_MAX+1.);

      // Test: Choose lattice[i][j] as perfect minimum. 
      // lattice[i][j]=(lattice[(i+1)%N][j]+lattice[i][(j+1)%N]+lattice[(i-1+N)%N][j]+lattice[i][(j-1+N)%N])/4.;
      // End Test. 

      HamPartO=cos(oldAngle-lattice[(i+1)%N][j]);
      HamPartO+=cos(oldAngle-lattice[i][(j+1)%N]);
      HamPartO+=cos(oldAngle-lattice[(i-1+N)%N][j]);
      HamPartO+=cos(oldAngle-lattice[i][(j-1+N)%N]);
      // Bidirectional = 2.*
      //HamPartO*=2.;

      HamPartN=cos(lattice[i][j]-lattice[(i+1)%N][j]);
      HamPartN+=cos(lattice[i][j]-lattice[i][(j+1)%N]);
      HamPartN+=cos(lattice[i][j]-lattice[(i-1+N)%N][j]);
      HamPartN+=cos(lattice[i][j]-lattice[i][(j-1+N)%N]);
      // Bidirectional = 2.*
      //HamPartN*=2.;

      // Bidirectional = 2.*
      deltaH=2.*(HamPartN-HamPartO);

      //newHam=hamiltonian(lattice);
      //deltaH=newHam-deltaH;
      double p=std::min(1.,exp(deltaH / (*T)));
      //std::cout << "p=" << p << std::endl;
      if ((1.0*random()/(RAND_MAX+1.)) <= p) {
	//std::cout << deltaH << "\t" << exp(-deltaH / (*T)) << std::endl;
	//std::cout << "Taken." << std::endl;
	//std::cout << "Flipped, Delta H: " << deltaH << std::endl;
	(*T)=1./log(k);
	//deltaH=newHam;
      } else {
	//std::cout << "Not taken." << std::endl;
	lattice[i][j]=oldAngle;
	//deltaH=oldHam;
      }
    }
  }
}

double magnetisation(double lattice[N][N]) {
  double magsin=0;
  double magcos=0;
  double magabs;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      magsin+=sin(lattice[i][j]);
      magcos+=cos(lattice[i][j]);
    }
  }
  magabs=sqrt(magcos*magcos+magsin*magsin);
  std::cout << "Magnetisation x: " << magcos << std::endl;
  std::cout << "Magnetisation y: " << magsin << std::endl;
  std::cout << "abs(Magnetisation): " << magabs << std::endl;
  return magabs;
}

int main(int argc, char **argv) {
  double lattice[N][N];
  int iter=10000;
  int printstep=5;
  int drawstep=1;
  int nanoseconds=100000;
  timespec sleepPeriod = { 0, nanoseconds };
  timespec unusedPeriod;

  srandom(time(NULL));

  // Open files:
  std::ofstream magfile;
  magfile.open("magnetisation.dat");

  // Initialize SDL: 
  SDL_Surface *screen;
  if (SDL_Init(SDL_INIT_VIDEO) < 0 ) return 1;
   
  if (!(screen = SDL_SetVideoMode(WIDTH, HEIGHT, DEPTH, SDL_HWSURFACE))) {
    SDL_Quit();
    return 1;
  }
  
  // Key to break it
  SDL_Event event;

  // Simple Pixel
  Uint32 simplepix = SDL_MapRGB( screen->format, 0, 0xFF, 0xFF ); 

  // Surface to paint on: 
  SDL_Surface *paintme = NULL; 
  
  paintme = SDL_CreateRGBSurface( SDL_HWSURFACE, screen->w, screen->h, screen->format->BitsPerPixel, screen->format->Rmask, screen->format->Gmask, screen->format->Bmask, 0 ); 
    
  // Start xymodel: 
  double T=100.0;
  randLattice(lattice);

  for (int k = 0; k < iter; ++k) {
    if (k%printstep==0) {
      //nanosleep(&sleepPeriod, &unusedPeriod);
      //system("clear");
      std::cout << "Iteration: " << k << std::endl;
      //printLattice(lattice);
      std::cout << "Energy: " << hamiltonian(lattice) << std::endl;;

      magfile << k << "\t" << magnetisation(lattice) << std::endl;
    }

    if (k%drawstep==0) {
      SDLdrawLattice(lattice,paintme,screen);
      SDL_WM_SetCaption("xy Model", NULL);
    }

    turnSpinS(lattice,&T,k*N*N);
    //turnSpinR(lattice,&T,k*N*N);
    if (k%printstep==0) 
      std::cout << "Temperature: " << T << std::endl;
    
    // Shall we quit?
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
	// Quit!
	SDL_Quit();
	magfile.close();
	return 0;
      }
    }
  }

  magfile.close();
  return 0;
}
