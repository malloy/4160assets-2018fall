// Brian Malloy, Object Technology with C++
// Example of keyboard bounce 
#include <SDL.h>
#include <iostream>
#include <string>
#include "ioManager.h"

void drawBackground(SDL_Surface* screen) {
  SDL_FillRect( screen, NULL, 
    SDL_MapRGB(screen->format, 0xff, 0xff, 0xff) );
  SDL_Rect dest = {0, 0, 0, 0};
  SDL_BlitSurface( screen, NULL, screen, &dest );
}

int main() {
  try {
    IOManager& io = IOManager::getInstance();
    SDL_Surface* screen = io.getScreen();

    SDL_Event event;
    int tcount = 0, pcount = 0;
    while (true) {
      drawBackground(screen);
      io.printMessageAt("Press <r> key to reset", 40, 10);
      Uint8 *keystate = SDL_GetKeyState(NULL);
      SDL_PollEvent(&event);
      if (event.type == SDL_QUIT) break;
      if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_ESCAPE) break;
        if (event.key.keysym.sym == SDLK_t) {
          ++tcount;
        }
        if (keystate[SDLK_p]) {
          ++pcount;
        }
        if (keystate[SDLK_r]) {
          pcount = 0;
          tcount = 0;
        }
      }
      io.printMessageValueAt("T's: ", tcount, 40, 40);
      io.printMessageValueAt("P's: ", pcount, 40, 70);
      SDL_Flip(screen);
    }
  }
  catch(const std::string& msg) { std::cout << msg << std::endl;  }
  catch(...) { std::cout << "oops" << std::endl;  }
  return 0;
}
