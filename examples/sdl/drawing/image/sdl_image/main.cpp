// The basis of this example was obtained from:
// https://wiki.libsdl.org/SDL_CreateRenderer
// The original example was modified by Brian Malloy, Jan 2017

// To compile and link, need to add link flag in Makefile: -lSDL2_image
// Also need to install libsdl2-image-dev

#include <iostream>
#include "SDL.h"
#include "SDL_image.h"

int main( ) {
  int posX = 100, posY = 100, width = 320, height = 240;
  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window *win = 
    SDL_CreateWindow("Hello World", posX, posY, width, height, 0);

  SDL_Renderer *renderer = 
    SDL_CreateRenderer(win, -1, SDL_RENDERER_PRESENTVSYNC);

  // Now we can load rgb or rgba:
  SDL_Surface *surface = IMG_Load("images/hello.bmp");
  if ( surface==NULL ) {
    std::cout << "Couldn't load images/hello.bmp" << std::endl;
    return 1;
  }

  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);

  const Uint8* keystate;
  while ( true ) {
    keystate = SDL_GetKeyboardState(nullptr);
    if (keystate[SDL_SCANCODE_ESCAPE]) { break; }

    SDL_Event event;
    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        break;
      }
    }

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
  }

  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(win);

  SDL_Quit();
}
