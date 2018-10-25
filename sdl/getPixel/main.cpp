#include <iostream>
#include "SDL.h"
#include "SDL_image.h"

void drawRectangle(SDL_Surface* surface) {
  SDL_Rect r = {200, 200, 200, 100};
  Uint32 red = SDL_MapRGB(surface->format, 255, 0, 0);
  SDL_FillRect( surface, &r, red );
}

// http://sdl.beuc.net/sdl.wiki/Pixel_Access
Uint32 getPixel(SDL_Surface *surface, int x, int y) {
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;
    case 2:
        return *(Uint16 *)p;
    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
    case 4:
        return *(Uint32 *)p;
    default:
        return 0;    // shouldn't happen, but avoids warnings
    }
}

void getPixelColor(SDL_Surface* surface, int x, int y) {
  SDL_LockSurface(surface);

  Uint32 pixel = getPixel(surface, x, y);

  Uint8 r, g, b, a;
  SDL_GetRGBA(pixel, surface->format, &r, &g, &b, &a);
  SDL_UnlockSurface(surface);
  std::cout << "color at (" << x << ", " << y << ") ";
  std::cout << " is: " << (int)r << ", " << (int)g << ", " << (int)b 
            << std::endl;
}

int main( ) {
  int winPosX = 100, winPosY = 100, width = 640, height = 480;
  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window *win = 
    SDL_CreateWindow("Hello World", winPosX, winPosY, width, height, 0);

  SDL_Renderer *renderer = 
    SDL_CreateRenderer(win, -1, SDL_RENDERER_PRESENTVSYNC);

  // Now we can load rgb or rgba:
  SDL_Surface *surface = IMG_Load("images/green.png");
  if ( surface==NULL ) {
    std::cout << "Couldn't load images/green.png" << std::endl;
    return 1;
  }

  drawRectangle(surface);
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, texture, NULL, NULL);
  getPixelColor(surface, 10, 10);
  getPixelColor(surface, 210, 210);
  SDL_RenderPresent(renderer);

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
  }

  SDL_FreeSurface(surface);
  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(win);

  SDL_Quit();
}
