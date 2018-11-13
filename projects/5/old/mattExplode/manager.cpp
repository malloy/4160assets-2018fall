#include <cmath>
#include "manager.h"
#include "explodingSprite.h"

Manager::~Manager() { 
  delete orbFrame;
  delete orb;
  delete gdata;
  SDL_FreeSurface(orbSurface);
}

Manager::Manager() :
  env( SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center")) ),
  gdata( Gamedata::getInstance() ),
  io( IOManager::getInstance() ),
  clock( Clock::getInstance() ),
  screen( io.getScreen() ),
  orbSurface( io.loadAndSet(gdata->getXmlStr("orbFile"), true) ),
  orbFrame(
    new Frame(orbSurface, 
          gdata->getXmlInt("orbWidth"), gdata->getXmlInt("orbHeight"),
          gdata->getXmlInt("orbSrcX"), gdata->getXmlInt("orbSrcY")) 
  ),
  orb( new Sprite(
    Vector2f(gdata->getXmlInt("orbX"), gdata->getXmlInt("orbY")),
    Vector2f(gdata->getXmlInt("orbXspeed"), gdata->getXmlInt("orbYspeed")),
    "orb",
    orbFrame)
  )
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    throw string("Unable to initialize SDL: ");
  }
  atexit(SDL_Quit);
}

void Manager::drawBackground() const {
  SDL_FillRect( screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255) );
  SDL_Rect dest = {0, 0, 0, 0};
  SDL_BlitSurface( screen, NULL, screen, &dest );
}

void Manager::play() {
  SDL_Event event;
  bool done = false;
  bool orbExploded = false;
  bool keyCatch = false;

  while ( not done ) {
    drawBackground();
    orb->draw();
    io.printMessageCenteredAt("Press <e> to explode the red orb", 20);
    io.printMessageCenteredAt("The orb should reappear where it exploded!", 40);
    orb->update(clock.getElapsedTicks());
    SDL_Flip(screen);

    if ( orbExploded ) {
      if ( static_cast<ExplodingSprite*>(orb)->chunkCount() == 0 ) {
        delete orb;
        orb = new Sprite(
          Vector2f(gdata->getXmlInt("orbX"), gdata->getXmlInt("orbY")),
          Vector2f(gdata->getXmlInt("orbXspeed"), 
                   gdata->getXmlInt("orbYspeed")),
          "orb", orbFrame);
        orbExploded = false;
      }
    }

    SDL_PollEvent(&event);
    if (event.type ==  SDL_QUIT) { break; }
    if(event.type == SDL_KEYUP) { keyCatch = false; }
    if(event.type == SDL_KEYDOWN) {
      switch ( event.key.keysym.sym ) {
        case SDLK_ESCAPE : done = true; break;
        case SDLK_q      : done = true; break;
        case SDLK_e      : {
          if (!orbExploded) {
            orbExploded = true;
            Sprite *temp = orb;
            orb = new ExplodingSprite(*orb);
            delete temp;
          }
          break;
        }
        case SDLK_p      : {
          if (!keyCatch) {
            keyCatch = true;
            if ( clock.isPaused() ) clock.unpause();
            else clock.pause();
          }
          break;
        }
        default          : break;
      }
    }
  }
}
