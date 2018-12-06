#include <iostream>
#include <string>
#include "multisprite.h"
#include "explodingSprite.h"
#include "smartSprite.h"
#include "gamedata.h"
#include "manager.h"

Manager::~Manager() { 
  // These deletions eliminate "definitely lost" and
  // "still reachable"s in Valgrind.
}

Manager::Manager() :
  env( SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center")) ),
  io( IOManager::getInstance() ),
  clock( Clock::getInstance() ),
  screen( io.getScreen() ),
  world("back", Gamedata::getInstance().getXmlInt("backFactor") ),
  viewport( Viewport::getInstance() ),
  currentSprite(0),
  flock( new FlockingSystem("flock"))
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    throw string("Unable to initialize SDL: ");
  }
  atexit(SDL_Quit);
  viewport.setObjectToTrack(flock->getFirstBoid());
}

void Manager::draw() const {
  world.draw();
  flock->draw();
  SDL_Flip(screen);
}

void Manager::update() {
  ++clock;
  Uint32 ticks = clock.getElapsedTicks();
  flock->update(ticks);
  world.update();
  viewport.update(); // always update viewport last
}

void Manager::play() {
  SDL_Event event;

  bool done = false;
  bool keyCatch = false;
  while ( not done ) {

    SDL_PollEvent(&event);
    Uint8 *keystate = SDL_GetKeyState(NULL);
    if (event.type ==  SDL_QUIT) { done = true; break; }
    if(event.type == SDL_KEYUP) { 
      keyCatch = false; 
    }
    if(event.type == SDL_KEYDOWN) {
      if (keystate[SDLK_ESCAPE] || keystate[SDLK_q]) {
        done = true;
        break;
      }
      if (keystate[SDLK_t] && !keyCatch) {
        keyCatch = true;
        std::cout << "Gotta fix tab to be next boid" << std::endl;
        //currentSprite = (currentSprite+1) % sprites.size();
        //viewport.setObjectToTrack(sprites[currentSprite]);
      }
      if (keystate[SDLK_p] && !keyCatch) {
        keyCatch = true;
        if ( clock.isPaused() ) clock.unpause();
        else clock.pause();
      }
      if (keystate[SDLK_s] && !keyCatch) {
        keyCatch = true;
        clock.toggleSloMo();
      }
      if (keystate[SDLK_p] && !keyCatch) {
        keyCatch = true;
        if ( clock.isPaused() ) clock.unpause();
        else clock.pause();
      }
      if (keystate[SDLK_PLUS] || keystate[SDLK_EQUALS]) { 
        if ( !keyCatch ) {
          keyCatch = true;
          SmartSprite::incrSafeDistance(); 
        }
      }
      if (keystate[SDLK_MINUS]) { 
        if ( !keyCatch ) {
          keyCatch = true;
          SmartSprite::decrSafeDistance();
        }
      }
    }

    draw();
    update();
  }
}
