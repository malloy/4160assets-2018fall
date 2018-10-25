// To compile and link, need to add link flag in Makefile: -lSDL2_image
// Also need to install libsdl2-image-dev

#include <iostream>
#include <string>
#include <SDL.h>
// The following is needed for IMG_LoadTexture:
#include <SDL_image.h>

const int WIDTH  = 320;
const int HEIGHT = 240;
const std::string imageName = "images/hello.bmp";

int main( ) {
  int posX = 100, posY = 100;
  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window *win = 
    SDL_CreateWindow("Hello World", posX, posY, WIDTH, HEIGHT, 0);

  SDL_Renderer *renderer = 
    SDL_CreateRenderer(win, -1, SDL_RENDERER_PRESENTVSYNC);

  // Now we can load rgb or rgba:
  SDL_Texture *texture = IMG_LoadTexture(renderer, imageName.c_str());
  if ( texture == NULL ) {
    std::cout << "Couldn't load " + imageName << std::endl;
    return 1;
  }

  SDL_Event event;
  const Uint8* keystate;
  int nKeys=-1;
  SDL_Rect srcrect = {0, 0, 320, 240};
  SDL_Rect dstrect = {0, 0, 320, 240};
  while ( true ) {
    keystate = SDL_GetKeyboardState(&nKeys);
    if (keystate[SDL_SCANCODE_ESCAPE]) { break; }

    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        break;
      }
    }

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, &srcrect, &dstrect);
    SDL_RenderPresent(renderer);
  }

  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(win);

  SDL_Quit();
}
