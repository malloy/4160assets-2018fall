// Brian Malloy        September, 2010

#include <cmath>  // for sqrtf
#include <iostream>
#include "health.h"

IOManager *IOManager::instance = NULL;

void drawBackground(SDL_Surface* screen) {
  SDL_FillRect( screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255) );
  SDL_Rect dest = {0, 0, 0, 0};
  SDL_BlitSurface( screen, NULL, screen, &dest );
}

void playGame() {
  SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center"));
  IOManager* io = IOManager::getInstance();
  SDL_Surface * const screen = io->getScreen();
  //const Uint32 BLUE = SDL_MapRGB(screen->format, 0x00, 0x00, 0xcd);
  //const Uint32 RED = SDL_MapRGB(screen->format, 0xff, 0, 0);
  atexit(SDL_Quit);

  SDL_Event event;
  bool done = false;
  Health bar;
  unsigned prevTicks = 0;
  unsigned currTicks = SDL_GetTicks();
  unsigned ticks = 0;
  while ( not done ) {
     drawBackground(screen);
     Uint8 *keystate = SDL_GetKeyState(NULL);
     if ( SDL_PollEvent(&event) )
     switch (event.type) {
       case SDL_QUIT: {
           done = true;
           break;
       }
       case SDL_KEYDOWN: {
         if (keystate[SDLK_ESCAPE] || keystate[SDLK_q]) {
           done = true;
           break;
         }
         if (keystate[SDLK_F1]) {
           bar.reset();
           break;
         }
       }
      }
     // **************** Draw Health Meter ********************
     bar.draw();
     io->printMessageCenteredAt("Press f1 to reset health meter", 10);
     currTicks = SDL_GetTicks();
     ticks = currTicks-prevTicks;
     prevTicks = currTicks;
     bar.update(ticks);

     SDL_Flip(screen);
  }
  delete io;
}

int main() {
   try {
      playGame();
   }
   catch (const string& msg) { std::cout << msg << std::endl; }
   catch (...) {
      std::cout << "Oops, someone threw an exception!" << std::endl;
   }
   return 0;
}
