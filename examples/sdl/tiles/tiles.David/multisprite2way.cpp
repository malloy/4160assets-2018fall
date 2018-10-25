#include <iostream>
#include <cmath>
#include "multisprite2way.h"
#include "gamedata.h"
#include "frameFactory.h"



void MultiframeSprite2Way::advanceFrame(Uint32 ticks) 
{
  float ms = 1000.0/frameInterval;
  dt += ticks;
  int df = dt / ms;
  dt -= df * ms;
  
  currentFrame = (currentFrame + df) % numberOfFrames;
}

MultiframeSprite2Way::MultiframeSprite2Way( const std::string& name, 
                  const std::vector<Frame*> & fms) :
  Drawable(name, 
           Vector2f(Gamedata::getInstance()->getXmlInt(name+"X"), 
                    Gamedata::getInstance()->getXmlInt(name+"Y")), 
           Vector2f(Gamedata::getInstance()->getXmlInt(name+"SpeedX"),
                    Gamedata::getInstance()->getXmlInt(name+"SpeedY"))
           ),
  frames(fms),
  frameWidth(fms[0]->getWidth()),
  frameHeight(fms[0]->getHeight()),
  worldWidth(Gamedata::getInstance()->getXmlInt("worldWidth")),
  worldHeight(Gamedata::getInstance()->getXmlInt("worldHeight")),
  dt(0),
  currentFrame(0),
  currentLayer(0),
  numberOfFrames( Gamedata::getInstance()->getXmlInt(name+"Frames") ),
  frameInterval( Gamedata::getInstance()->getXmlInt(name+"FrameInterval") )
{ }

MultiframeSprite2Way::MultiframeSprite2Way( const std::string& name) :
  Drawable(name, 
    Vector2f(Gamedata::getInstance()->getXmlInt(name+"X"), 
      Gamedata::getInstance()->getXmlInt(name+"Y")), 
    Vector2f(Gamedata::getInstance()->getXmlInt(name+"SpeedX"),
      Gamedata::getInstance()->getXmlInt(name+"SpeedY"))
  ), 
  frames(FrameFactory::getInstance().getMFrames(name, 2)),
  frameWidth(frames[0]->getWidth()),
  frameHeight(frames[0]->getHeight()),
  worldWidth(Gamedata::getInstance()->getXmlInt("worldWidth")),
  worldHeight(Gamedata::getInstance()->getXmlInt("worldHeight")),
  dt(0),
  currentFrame(0),
  currentLayer(0),
  numberOfFrames( Gamedata::getInstance()->getXmlInt(name+"Frames") ),
  frameInterval( Gamedata::getInstance()->getXmlInt(name+"FrameInterval") )
{ }


MultiframeSprite2Way::MultiframeSprite2Way(const MultiframeSprite2Way& s) :
  Drawable(s.getName(), s.getPosition(), s.getVelocity()),
  frames(s.frames),
  frameWidth(s.getFrame()->getWidth()),
  frameHeight(s.getFrame()->getHeight()),
  worldWidth(Gamedata::getInstance()->getXmlInt("worldWidth")),
  worldHeight(Gamedata::getInstance()->getXmlInt("worldHeight")),
  dt(s.dt),
  currentFrame(s.currentFrame),
  currentLayer(s.currentLayer),
  numberOfFrames( s.numberOfFrames ),
  frameInterval( s.frameInterval )
  { }

void MultiframeSprite2Way::draw() const 
{ 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  
  frames[(numberOfFrames*currentLayer)+currentFrame]->draw(x, y);
}

void MultiframeSprite2Way::update(Uint32 ticks) 
{ 
  advanceFrame(ticks);

  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( Y() < 0) 
  {
    velocityY( abs( velocityY() ) );
  }
  if ( Y() > worldHeight-frameHeight) 
  {
    velocityY( -abs( velocityY() ) );
  }
  if ( X() < 0) {
    velocityX( abs( velocityX() ) );
  }
  if ( X() > worldWidth-frameWidth) 
  {
    velocityX( -abs( velocityX() ) );
  }  
  
  if ( velocityY() < 0)  currentLayer=0;
  else  currentLayer=1;
}





