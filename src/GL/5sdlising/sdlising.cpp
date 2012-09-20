#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <SDL/SDL.h>

#define N 700
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

double hamiltonian(int lattice[N][N]) {
  double sum=0;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      sum+=2*lattice[i][j]*lattice[(i+1)%N][j];
      sum+=2*lattice[i][j]*lattice[i][(j+1)%N];
      //sum+=lattice[i][j]*lattice[(i-1+N)%N][j];
      //sum+=lattice[i][j]*lattice[i][(j-1+N)%N];
    }
  }
  return -1./2.*J*sum;
}

int printLattice(int lattice[N][N]) {
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

int SDLdrawLattice(int lattice[N][N], SDL_Surface *paintme, SDL_Surface *screen) {
  // Simple Pixel Cold
  Uint32 coldpix = SDL_MapRGB( screen->format, 0, 0, 0xFF ); 

  // Simple Pixel Warm
  Uint32 warmpix = SDL_MapRGB( screen->format, 0xFF, 0, 0 ); 

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j)	{
      if (lattice[i][j] == 1) {
	for (int k = 0; k < HEIGHT/N; ++k) {
	  for (int l = 0; l < WIDTH/N; ++l) {
	    put_pixel32( paintme, i*HEIGHT/N+k, j*WIDTH/N+l, warmpix );
	  }
	}
      } else {
	for (int k = 0; k < HEIGHT/N; ++k) {
	  for (int l = 0; l < WIDTH/N; ++l) {
	    put_pixel32( paintme, i*HEIGHT/N+k, j*WIDTH/N+l, coldpix );
	    //std::cout << "cold: " << "i: " << i*HEIGHT/N-k << "  j:" << j*WIDTH/N-l << std::endl;
	  }
	}
      }
    }
    //std::cout << std::endl;
  }
  std::cout << "Energy: " << hamiltonian(lattice) << std::endl;;
  apply_surface( 0, 0, paintme, screen ); 
  SDL_Flip( screen );
  //SDL_Delay( 10 ); 
}

int randLattice(int lattice[N][N]) {
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j)	{
      lattice[i][j]=((1.0*random()/(RAND_MAX+1.))>0.5) ? -1 : 1;
    }
  }
}

int flipSpinR(int lattice[N][N], double *T, int k) {
  int i=(N*1.0*random()/(RAND_MAX+1.));
  int j=(N*1.0*random()/(RAND_MAX+1.));
  //double oldHam=hamiltonian(lattice);
  //double newHam
  double HamPart=0, deltaH;
  //deltaH=oldHam;
  HamPart+=lattice[i][j]*lattice[(i+1)%N][j];
  HamPart+=lattice[i][j]*lattice[i][(j+1)%N];
  HamPart+=lattice[i][j]*lattice[(i-1+N)%N][j];
  HamPart+=lattice[i][j]*lattice[i][(j-1+N)%N];
  // Factor 2 because: 
  // 2* for bidirectional interaction
  HamPart*=2;

  //oldHam=hamiltonian(lattice);
  lattice[i][j]*=-1;
  //newHam=hamiltonian(lattice);
  //deltaH=newHam-deltaH;
  deltaH=HamPart;
  //std::cout << newHam-oldHam << std::endl;
  //std::cout << lattice[i][j] << " -- " << deltaH << std::endl;

  //std::cout << "Flipped, Delta H: " << deltaH << std::endl;
  double p=std::min(1.,exp(-deltaH / (*T)));
  //std::cout << "p=" << p << std::endl;
  if ((1.0*random()/(RAND_MAX+1.)) <= p) {
    //std::cout << "Taken." << std::endl;
    (*T)=1/log(k);
    //deltaH=newHam;
  } else {
    //std::cout << "Not taken." << std::endl;
    lattice[i][j]*=-1;
    //deltaH=oldHam;
  }
}

int flipSpinS(int lattice[N][N], double *T, int k) {
  //int i=(N*1.0*random()/(RAND_MAX+1.));
  //int j=(N*1.0*random()/(RAND_MAX+1.));
  //double oldHam=hamiltonian(lattice);
  //double newHam;
  double HamPart, deltaH;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      HamPart=0;
      HamPart+=lattice[i][j]*lattice[(i+1)%N][j];
      HamPart+=lattice[i][j]*lattice[i][(j+1)%N];
      HamPart+=lattice[i][j]*lattice[(i-1+N)%N][j];
      HamPart+=lattice[i][j]*lattice[i][(j-1+N)%N];
      // Factor 2 because: 
      // 2* for bidirectional interaction
      HamPart*=2;

      deltaH=HamPart;
      lattice[i][j]*=-1;
      //newHam=hamiltonian(lattice);
      //deltaH=newHam-deltaH;
      //std::cout << "Flipped, Delta H: " << deltaH << std::endl;
      double p=std::min(1.,exp(-deltaH / (*T)));
      //std::cout << "p=" << p << std::endl;
      if ((1.0*random()/(RAND_MAX+1.)) <= p) {
	//std::cout << "Taken." << std::endl;
	(*T)=1/log(k);
	//deltaH=newHam;
      } else {
	//std::cout << "Not taken." << std::endl;
	lattice[i][j]*=-1;
	//deltaH=oldHam;
      }
    }
  }
}

int main(int argc, char **argv) {
  int lattice[N][N];
  int iter=1000;
  int printstep=1;
  int nanoseconds=100000;
  timespec sleepPeriod = { 0, nanoseconds };
  timespec unusedPeriod;

  srandom(time(NULL));

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
    
  // Start Ising: 
  double T=10;
  randLattice(lattice);

  for (int k = 0; k < iter; ++k) {
    if (k%printstep==0) {
      //nanosleep(&sleepPeriod, &unusedPeriod);
      //system("clear");
      std::cout << "Iteration: " << k << std::endl;
      //printLattice(lattice);      
      SDLdrawLattice(lattice,paintme,screen);
      SDL_WM_SetCaption("Ising Model", NULL);
    }
    flipSpinS(lattice,&T,k);
    if (k%printstep==0) 
      std::cout << "Temperature: " << T << std::endl;
    
    // Shall we quit?
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
	// Quit!
	SDL_Quit();
	return 0;
      }
    }
  }
  
  return 0;
}
