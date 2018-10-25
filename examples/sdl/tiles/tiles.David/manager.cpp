#include <cmath>
#include "manager.h"
#include "spriteFactory.h"


//--------------------------------
#include <iostream>
#include <sstream>
//--------------------------------

Manager::~Manager() 
{ 
  delete Gamedata::getInstance();
}


Manager::Manager() :
  env( SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center")) ),
  info(false),
  infosprite(Sprite ("info")),
  gdata( Gamedata::getInstance() ),
  io( IOManager::getInstance() ),
  clock( Clock::getInstance() ),
  screen( io.getScreen() ),
  backSurface( io.loadAndSet(gdata->getXmlStr("back"), false) ),
  world(new Frame(backSurface,
                gdata->getXmlInt("viewWidth"), 
                gdata->getXmlInt("viewHeight"), 0, 0) ),
  tilefloor (TileSprite("tilefloor")),
  viewport( Viewport::getInstance() )
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0) 
  {
    throw string("Unable to initialize SDL: ");
  }
  
  MultiframeSprite2Way toast = MultiframeSprite2Way ("charactermulti2way");
  SpriteFactory::getInstance().addSprite (
    "charactermulti2way", SpriteFactory::MULTI_SPRITE_2WAY );
  SpriteFactory::getInstance().addSprite (
    "explosion", SpriteFactory::MULTI_SPRITE );
  
  
  viewport.setObjectToTrack (
    SpriteFactory::getInstance().getCurrent());
    
  atexit(SDL_Quit);
}


void Manager::draw() const 
{
  world.draw();
  tilefloor.draw();
  viewport.draw();
  
  std::map<std::string, Drawable*>::iterator itSprite = 
    SpriteFactory::getInstance().begin();
  while ( itSprite != SpriteFactory::getInstance().end() ) 
  {
    itSprite->second->draw();
    ++itSprite;
  }
  
  if (info) 
  {
    infosprite.draw();
    io.printMessageAt("Information", 10, 10);
    io.printMessageAt("Commands:", 10, 30);
    io.printMessageAt("q: quit", 20, 50);
    io.printMessageAt("t: switch sprite", 20, 70);
    io.printMessageAt("p: pause", 20, 90);
    io.printMessageAt("F1: info", 20, 110);
    io.printMessageAt("Currently Tracking: ", 10, 140);
    io.printMessageAt(
      SpriteFactory::getInstance().getCurrent()->getName(), 20, 160);
  }
  else
  {
    io.printMessageCenteredAt("Press t to switch sprites", 10);
    IOManager::getInstance().
      printMessageCenteredAt("Tracking "+
        SpriteFactory::getInstance().getCurrent()->getName(), 30);
        
    std::stringstream ss (std::stringstream::in | std::stringstream::out);
    ss << tilefloor.get_viewY();
    
    io.printMessageCenteredAt(ss.str(), 50);

  }
}

void Manager::update(Uint32 ticks) 
{
  std::map<std::string, Drawable*>::iterator itSprite = 
    SpriteFactory::getInstance().begin();
  while ( itSprite != SpriteFactory::getInstance().end() ) 
  {
    itSprite->second->update(ticks);
    ++itSprite;
  }
  viewport.update();
  tilefloor.update(ticks);
  world.update();
}

void Manager::play() 
{
  SDL_Event event;

  bool done = false;
  bool keyCatch = false;
  while ( not done ) {
    draw();
    SDL_Flip(screen);

    Uint32 ticks = clock.getElapsedTicks();
    update(ticks);

    SDL_PollEvent(&event);
    
    if (event.type ==  SDL_QUIT) { break; }
    if(event.type == SDL_KEYUP) { keyCatch = false; }
    if(event.type == SDL_KEYDOWN) {
      switch ( event.key.keysym.sym ) {
        case SDLK_ESCAPE : done = true; break;
        case SDLK_q      : done = true; break;
        case SDLK_t :
          if ( !keyCatch ) {
            keyCatch = true;
            info = false;
            viewport.setObjectToTrack (
              SpriteFactory::getInstance().getNext() );
          }
          break;
        case SDLK_p      : {
          if (!keyCatch) {
            keyCatch = true;
            if ( clock.isPaused() ) clock.unpause();
            else clock.pause();
          }
          break;
        }
        case SDLK_F1     : 
          if (!keyCatch)
          {
            keyCatch=true;
            if (info) 
            {
              info = false;
              viewport.setObjectToTrack (
                SpriteFactory::getInstance().getCurrent());
            }
            else
            {
              info = true;
              viewport.setObjectToTrack (&infosprite);
            }
          }
          break;
        default          : break;
      }
    }
  }
}




