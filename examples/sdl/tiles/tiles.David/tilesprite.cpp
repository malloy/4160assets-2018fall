#include <iostream>
#include <cmath>
#include <limits>

#include "tilesprite.h"
#include "gamedata.h"
#include "frameFactory.h"
#include "viewport.h"


using std::cout; using std::endl;


TileSprite::TileSprite(const std::string& name, const Frame* fm) :
  Drawable(name,
           Vector2f(Gamedata::getInstance()->getXmlInt(name+"X"), 
                    Gamedata::getInstance()->getXmlInt(name+"Y")), 
           Vector2f(
       (rand()%2?1:-1)*
       Gamedata::getInstance()->getXmlInt(name+"SpeedX"),
       (rand()%2?1:-1)*
       Gamedata::getInstance()->getXmlInt(name+"SpeedY"))
  ), 
  frame(fm),
  frameWidth(fm->getWidth()),
  frameHeight(fm->getHeight()),
  worldWidth(Gamedata::getInstance()->getXmlInt("worldWidth")),
  worldHeight(Gamedata::getInstance()->getXmlInt("worldHeight")),
  viewX(0.0),
  viewY(0.0),
  factor(1),
  demo(Gamedata::getInstance()->getXmlBool("demo")),
  view(Viewport::getInstance())
{ }

TileSprite::TileSprite( const string& name) :
  Drawable(name, 
           Vector2f(Gamedata::getInstance()->getXmlInt(name+"X"), 
                    Gamedata::getInstance()->getXmlInt(name+"Y")), 
           Vector2f(Gamedata::getInstance()->getXmlInt(name+"SpeedX"),
                    Gamedata::getInstance()->getXmlInt(name+"SpeedY"))
  ), 
  frame( FrameFactory::getInstance().getFrame(name) ),
  frameWidth(frame->getWidth()),
  frameHeight(frame->getHeight()),
  worldWidth(Gamedata::getInstance()->getXmlInt("worldWidth")),
  worldHeight(Gamedata::getInstance()->getXmlInt("worldHeight")),
  viewX(0.0),
  viewY(0.0),
  factor(1),
  view(Viewport::getInstance())
{ }

TileSprite::TileSprite(const TileSprite& s) :
  Drawable(s.getName(), s.getPosition(), s.getVelocity()), 
  frame(s.frame),
  frameWidth(s.getFrame()->getWidth()),
  frameHeight(s.getFrame()->getHeight()),
  worldWidth(Gamedata::getInstance()->getXmlInt("worldWidth")),
  worldHeight(Gamedata::getInstance()->getXmlInt("worldHeight")),
  viewX(s.viewX),
  viewY(s.viewY),
  factor(s.factor),
  view(Viewport::getInstance())
{ }

TileSprite& TileSprite::operator=(const TileSprite& rhs) {
  setName( rhs.getName() );
  setPosition(rhs.getPosition());
  setVelocity(rhs.getVelocity());
  frame = rhs.frame;
  frameWidth = rhs.frameWidth;
  frameHeight = rhs.frameHeight;
  worldWidth = Gamedata::getInstance()->getXmlInt("worldWidth");
  worldHeight = Gamedata::getInstance()->getXmlInt("worldHeight");
  viewX = rhs.viewX;
  viewY = rhs.viewY;
  factor = rhs.factor;
  //view = Viewport::getInstance();
  return *this;
}

void TileSprite::draw() const 
{ 
  float i, j;
  if (demo)
  {
    for (i=view.Y()-viewY+frameHeight; 
      i<view.Y()+view.height()-frameHeight; 
      i+=frameHeight)
    {
      for (j=view.X()-viewX+frameWidth; 
        j<view.X()+view.width()-frameWidth; 
        j+=frameWidth)
      {
        frame->draw(j, i); 
      }
    }  
  }
  else
  {
    for (i=view.Y()-viewY; 
      i<view.Y()+view.height(); 
      i+=frameHeight)
    {
      for (j=view.X()-viewX; 
        j<view.X()+view.width(); 
        j+=frameWidth)
      {
        frame->draw(j, i); 
      }
    }
  }
}

unsigned TileSprite::getPixel(Uint32 i, Uint32 j) const 
{ 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  x = i - x;
  y = j - y;
  Uint32 *pixels = static_cast<Uint32 *>(frame->getSurface()->pixels);
  return pixels[ ( y * frame->getWidth() ) + x ];
}

int TileSprite::getDistance(const TileSprite *obj) const 
{ 
  return hypot(X()-obj->X(), Y()-obj->Y());
}

void TileSprite::update(Uint32 ticks) 
{ 
  demo =  Gamedata::getInstance()->getXmlBool("demo");
  viewX = static_cast<int>(view.X() / factor) % frameWidth;
  viewY = static_cast<int>(view.Y() / factor) % frameHeight;
}




