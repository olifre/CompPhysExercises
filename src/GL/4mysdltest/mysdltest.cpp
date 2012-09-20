#include <stdio.h>
#include "SDL/SDL.h"

#define WIDTH 640
#define HEIGHT 480
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

int main(int argc, char* argv[]) {
    SDL_Surface *screen;
    SDL_Event event;
    int keypress = 0;
    int h=0; 
  
    if (SDL_Init(SDL_INIT_VIDEO) < 0 ) return 1;
   
    if (!(screen = SDL_SetVideoMode(WIDTH, HEIGHT, DEPTH, SDL_SWSURFACE))) {
        SDL_Quit();
        return 1;
    }

    SDL_Surface *paintme = NULL; 

    paintme = SDL_CreateRGBSurface( SDL_SWSURFACE, screen->w, screen->h, screen->format->BitsPerPixel, screen->format->Rmask, screen->format->Gmask, screen->format->Bmask, 0 ); 

    // Simple Pixel
    Uint32 simplepix = SDL_MapRGB( screen->format, 0, 0xFF, 0xFF ); 

    //If the surface must be locked 
    //if( SDL_MUSTLOCK( paintme ) ) { 
      //Lock the surface 
    //  SDL_LockSurface( paintme ); 
    //} 

    for (int i=0; i<100; i++) {
      put_pixel32( paintme, i, i, simplepix ); 
    }

    //Unlock surface 
    //if( SDL_MUSTLOCK( paintme ) ) { 
    //  SDL_UnlockSurface( paintme ); 
    //}
    
    //Copy color key 
    //if( screen->flags & SDL_SRCCOLORKEY ) { 
    //  SDL_SetColorKey( paintme, SDL_RLEACCEL | SDL_SRCCOLORKEY, screen->format->colorkey ); 
    //} 
    
    apply_surface( 0, 0, paintme, screen ); 

    SDL_Flip( screen );
  
    SDL_Delay( 2000 ); 

    SDL_Quit();
  
    return 0;
}
