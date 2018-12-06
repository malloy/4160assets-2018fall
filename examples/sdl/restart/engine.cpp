#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <random>
#include <iomanip>
#include "sprite.h"
#include "multisprite.h"
#include "gamedata.h"
#include "engine.h"
#include "frameGenerator.h"

Engine::~Engine() { 
  std::cout << "Terminating program" << std::endl;
  for ( auto it : sprites ) {
    delete it;
  }
}

Engine::Engine() :
  rc( RenderContext::getInstance() ),
  io( IOmod::getInstance() ),
  clock( Clock::getInstance() ),
  renderer( rc->getRenderer() ),
  world("back", Gamedata::getInstance().getXmlInt("back/factor") ),
  viewport( Viewport::getInstance() ),
  player("coin"),
  sprites(),
  currentSprite(0),
  makeVideo( false )
{
  Drawable* s = new Sprite("yellowstar");
  s->setScale(2);
  sprites.push_back(s);

  s = new Sprite("yellowstar");
  sprites.push_back(s);

  sprites.push_back( new MultiSprite("SpinningStar") );

  Viewport::getInstance().setObjectToTrack(&player);
  std::cout << "Loading complete" << std::endl;
}

void Engine::printScales() const {
  for (Drawable* s : sprites) {
    std::cout << s->getScale() << std::endl;
  }
}


void Engine::draw() const {
  world.draw();
  std::stringstream strm;
  strm << "fps: " << clock.getFps();
  io.writeText(strm.str(), 30, 60);
  if ( sprites.size() == 0 ) {
    io.writeText("Press R to Restart the game", 250, 200);
    clock.pause();
  }
  strm.clear();
  strm.str("");
  strm << sprites.size() << " sprites remaining";
  io.writeText(strm.str(), 30, 90);
  io.writeText("Press E to explode a sprite", 450, 30);
  io.writeText("Restart when all sprites are exploded", 450, 60);

  for(auto* s : sprites) s->draw();
  player.draw();
  viewport.draw();
  SDL_RenderPresent(renderer);
}


void Engine::update(Uint32 ticks) {
  for(auto* s : sprites) s->update(ticks);
  player.update(ticks);

  std::vector<Drawable*>::iterator ptr = sprites.begin();
  while ( ptr != sprites.end() ) {
    if ( (*ptr)->explosionDone() ) {
      ptr = sprites.erase(ptr);
    }
    else ++ptr;
  }
  
  world.update();
  viewport.update(); // always update viewport last
}

void Engine::switchSprite(){
  if ( sprites.size() == 0 ) return;
  ++currentSprite;
  currentSprite = currentSprite % sprites.size();
  //Viewport::getInstance().setObjectToTrack(sprites[currentSprite]);
}

bool Engine::play() {
  SDL_Event event;
  const Uint8* keystate;
  bool done = false;
  Uint32 ticks = clock.getElapsedTicks();
  FrameGenerator frameGen;

  while ( !done ) {
    // The next loop polls for events, guarding against key bounce:
    while ( SDL_PollEvent(&event) ) {
      keystate = SDL_GetKeyboardState(NULL);
      if (event.type ==  SDL_QUIT) { done = true; break; }
      if(event.type == SDL_KEYDOWN) {
        if (keystate[SDL_SCANCODE_ESCAPE] || keystate[SDL_SCANCODE_Q]) {
          done = true;
          break;
        }
        if ( keystate[SDL_SCANCODE_P] ) {
          if ( clock.isPaused() ) clock.unpause();
          else clock.pause();
        }
        if ( keystate[SDL_SCANCODE_R] ) {
          clock.unpause();
          return true;
        }
        if ( keystate[SDL_SCANCODE_T] ) {
          // Disabled for this demo
          // switchSprite();
        }
        if ( keystate[SDL_SCANCODE_E] ) {
          sprites[currentSprite]->explode();
          switchSprite();
        }
        if (keystate[SDL_SCANCODE_F4] && !makeVideo) {
          std::cout << "Initiating frame capture" << std::endl;
          makeVideo = true;
        }
        else if (keystate[SDL_SCANCODE_F4] && makeVideo) {
          std::cout << "Terminating frame capture" << std::endl;
          makeVideo = false;
        }
      }
    }

    ticks = clock.getElapsedTicks();
    if ( ticks > 0 ) {
      clock.incrFrame();
      draw();
      update(ticks);
      if ( makeVideo ) {
        frameGen.makeFrame();
      }
    }
  }
  return false;
}
