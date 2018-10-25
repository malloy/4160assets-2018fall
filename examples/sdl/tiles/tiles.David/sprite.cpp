#include <iostream>
#include <cmath>
#include <limits>
#include "sprite.h"
#include "gamedata.h"
#include "frameFactory.h"

using std::cout; using std::endl;

float getRand(int min, int max) {
  return min + (rand() / (std::numeric_limits<int>::max()+1.0f))*(max-min);
}

Sprite::Sprite(const std::string& name, const Frame* fm) :
  Drawable(name,
           Vector2f(Gamedata::getInstance()->getXmlInt(name+"X"), 
                    Gamedata::getInstance()->getXmlInt(name+"Y")), 
           Vector2f(
       (rand()%2?1:-1)*
       getRand(10, Gamedata::getInstance()->getXmlInt(name+"SpeedX")),
       (rand()%2?1:-1)*
       getRand(10, Gamedata::getInstance()->getXmlInt(name+"SpeedY")))
  ), 
  frame(fm),
  frameWidth(fm->getWidth()),
  frameHeight(fm->getHeight()),
  worldWidth(Gamedata::getInstance()->getXmlInt("worldWidth")),
  worldHeight(Gamedata::getInstance()->getXmlInt("worldHeight"))
{ }

Sprite::Sprite( const string& name) :
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
  worldHeight(Gamedata::getInstance()->getXmlInt("worldHeight"))
{ }

Sprite::Sprite(const Sprite& s) :
  Drawable(s.getName(), s.getPosition(), s.getVelocity()), 
  frame(s.frame),
  frameWidth(s.getFrame()->getWidth()),
  frameHeight(s.getFrame()->getHeight()),
  worldWidth(Gamedata::getInstance()->getXmlInt("worldWidth")),
  worldHeight(Gamedata::getInstance()->getXmlInt("worldHeight"))
{ }

Sprite& Sprite::operator=(const Sprite& rhs) 
{
  setName( rhs.getName() );
  setPosition(rhs.getPosition());
  setVelocity(rhs.getVelocity());
  frame = rhs.frame;
  frameWidth = rhs.frameWidth;
  frameHeight = rhs.frameHeight;
  worldWidth = Gamedata::getInstance()->getXmlInt("worldWidth");
  worldHeight = Gamedata::getInstance()->getXmlInt("worldHeight");
  return *this;
}

void Sprite::draw() const { 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  frame->draw(x, y); 
}

unsigned Sprite::getPixel(Uint32 i, Uint32 j) const { 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  x = i - x;
  y = j - y;
  Uint32 *pixels = static_cast<Uint32 *>(frame->getSurface()->pixels);
  return pixels[ ( y * frame->getWidth() ) + x ];
}

int Sprite::getDistance(const Sprite *obj) const { 
  return hypot(X()-obj->X(), Y()-obj->Y());
}

void Sprite::update(Uint32 ticks) 
{ 
  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( Y() <= 0) {
    velocityY( abs( velocityY() ) );
    Y(0);
  }
  if ( Y() >= worldHeight-frameHeight) {
    velocityY( -abs( velocityY() ) );
    Y(worldHeight-frameHeight);
  }

  if ( X() <= 0) 
  {
    velocityX( abs( velocityX() ) );
    X(0);
  }
  if ( X() >= worldWidth-frameWidth) 
  {
    velocityX( -abs( velocityX() ) );
    X(worldWidth-frameWidth);
  }  
}




