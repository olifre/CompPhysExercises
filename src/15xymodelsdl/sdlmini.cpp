#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>

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

int SDLdrawPixel(SDL_Surface *paintme, SDL_Surface *screen) {
  // Simple Pixel Cold
  Uint32 coldpix = SDL_MapRGB( screen->format, 0, 0, 0xFF ); 

  // Simple Pixel Warm
  Uint32 warmpix = SDL_MapRGB( screen->format, 0xFF, 0, 0 ); 

  put_pixel32( paintme, HEIGHT/2, WIDTH/2, warmpix );
  put_pixel32( paintme, HEIGHT/2+1, WIDTH/2+1, coldpix );
  apply_surface( 0, 0, paintme, screen ); 
  SDL_Flip( screen );
  //SDL_Delay( 10 ); 
}

int main(int argc, char **argv) {
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
    
   SDLdrawPixel(paintme,screen);
   SDL_WM_SetCaption("Funny App", NULL);

   // Shall we quit?
   while (SDL_PollEvent(&event)) {
     if (event.type == SDL_QUIT) {
       // Quit!
       SDL_Quit();
       return 0;
     }
  }
  return 0;
}
