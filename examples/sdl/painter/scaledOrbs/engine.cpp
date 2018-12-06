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

// [capture clause] (parameters) -> return-type {body}
auto Less = [](const Drawable* ith, const Drawable* ithplusfirsteth) {
  return ith->getScale() < ithplusfirsteth->getScale();
};

class SpriteLess {
public:
  bool operator()(const Drawable* lhs, const Drawable* rhs) const {
    return lhs->getScale() < rhs->getScale();
  }
};

Engine::~Engine() { 
  std::cout << "Terminating program" << std::endl;
  std::vector<Drawable*>::iterator it = sprites.begin();
  while ( it != sprites.end() ) {
    delete *it;
    ++it;
  }
}

Engine::Engine() :
  rc( RenderContext::getInstance() ),
  io( IOmod::getInstance() ),
  clock( Clock::getInstance() ),
  renderer( rc->getRenderer() ),
  world("back", Gamedata::getInstance().getXmlInt("back/factor") ),
  viewport( Viewport::getInstance() ),
  sprites(),
  currentSprite(-1),

  makeVideo( false )
{
  
  sprites.push_back( new MultiSprite("SpinningStar") );
  unsigned int n = Gamedata::getInstance().getXmlInt("numberOfStars");
  for ( unsigned int i = 0; i < n; ++i ) {
    Drawable* s = new Sprite("YellowStar");
    float scale = Gamedata::getInstance().getRandFloat(0.5,2);
    s->setScale(scale);
    sprites.push_back(s);
  }
  std::vector<Drawable*>::iterator ptr = sprites.begin();
  ++ptr;
  sort(ptr, sprites.end(), Less);

  switchSprite();
  //printScales();
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

  for(auto* s : sprites) s->draw();

  viewport.draw();
  SDL_RenderPresent(renderer);
}

void Engine::update(Uint32 ticks) {
  for(auto* s : sprites) s->update(ticks);
  world.update();
  viewport.update(); // always update viewport last
}

void Engine::switchSprite(){
  ++currentSprite;
  currentSprite = currentSprite % sprites.size();
  Viewport::getInstance().setObjectToTrack(sprites[currentSprite]);
}

void Engine::play() {
  SDL_Event event;
  const Uint8* keystate;
  bool done = false;
  Uint32 ticks = clock.getElapsedTicks();
  FrameGenerator frameGen;

  while ( !done ) {
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
        if ( keystate[SDL_SCANCODE_S] ) {
          clock.toggleSloMo();
        }
        if ( keystate[SDL_SCANCODE_T] ) {
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
}
