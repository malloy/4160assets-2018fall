#include <iostream>
#include <cmath>
#include "kaceyMultisprite.h"
#include "gamedata.h"
#include "frameFactory.h"

void KaceyMultisprite::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
    currentFrame = (currentFrame+1) % numberOfFrames;
		timeSinceLastFrame = 0;
	}
}

KaceyMultisprite::KaceyMultisprite( const std::string& name) :
  Drawable(name, 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"X"), 
                    Gamedata::getInstance().getXmlInt(name+"Y")), 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"SpeedX"),
                    Gamedata::getInstance().getXmlInt(name+"SpeedY"))
           ),
  type( "KaceyMultisprite"),
  frames( FrameFactory::getInstance().getFrames(name) ),
  worldWidth(Gamedata::getInstance().getXmlInt("worldWidth")),
  worldHeight(Gamedata::getInstance().getXmlInt("worldHeight")),

  dt(0),
  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"Frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"FrameInterval") ),
  timeSinceLastFrame( 0 ),
  frameWidth(frames[0]->getWidth()),
  frameHeight(frames[0]->getHeight()),
  flipx(1.0),
  keyp(false)
{ }

KaceyMultisprite::KaceyMultisprite( const std::string& name, const Vector2f& posoffset, const Vector2f&  veloffset) :
  Drawable(name, 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"X") + posoffset[0], 
                    Gamedata::getInstance().getXmlInt(name+"Y") + posoffset[1]), 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"SpeedX") + veloffset[0],
                    Gamedata::getInstance().getXmlInt(name+"SpeedY") + veloffset[1])
           ),
  type( "KaceyMultisprite"),
  frames( FrameFactory::getInstance().getFrames(name) ),
  worldWidth(Gamedata::getInstance().getXmlInt("worldWidth")),
  worldHeight(Gamedata::getInstance().getXmlInt("worldHeight")),
  dt(0),
  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"Frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"FrameInterval") ),
  timeSinceLastFrame( 0 ),
  frameWidth(frames[0]->getWidth()),
  frameHeight(frames[0]->getHeight()),
  flipx(1.0),
  keyp(false)
{}
KaceyMultisprite::KaceyMultisprite(const std::string& name,
                         const Vector2f& pos, const Vector2f& vel,
                         const std::vector<Frame*>& fms) : 
  Drawable(name, pos, vel), 
  type( "KaceyMultisprite"),
  frames(fms),
  worldWidth(Gamedata::getInstance().getXmlInt("worldWidth")),
  worldHeight(Gamedata::getInstance().getXmlInt("worldHeight")),

  dt(0),
  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"Frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"FrameInterval") ),
  timeSinceLastFrame( 0 ),
  frameWidth(fms[0]->getWidth()),
  frameHeight(fms[0]->getHeight()),
  flipx(1.0),
  keyp(false)
{ }

KaceyMultisprite::KaceyMultisprite(const KaceyMultisprite& s) :
  Drawable(s.getName(), s.getPosition(), s.getVelocity()), 
  type( "KaceyMultisprite"),
  frames(s.frames),
  worldWidth( s.worldWidth ),
  worldHeight( s.worldHeight ),
  dt(s.dt),
  currentFrame(s.currentFrame),
  numberOfFrames( s.numberOfFrames ),
  frameInterval( s.frameInterval ),
  timeSinceLastFrame( s.timeSinceLastFrame ),
  frameWidth( s.frameWidth ),
  frameHeight( s.frameHeight ),
  flipx(1.0),
  keyp(s.keyp)
  { }

void KaceyMultisprite::draw() const { 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  frames[currentFrame]->draw(x, y, 0.0, flipx, 1);
}

void KaceyMultisprite::turnRight() {
	flipx = 1.0;
  keyp = true;
}
void KaceyMultisprite::turnLeft() {
	flipx = -1.0;
  keyp = true;
}
void KaceyMultisprite::update(Uint32 ticks) { 
  advanceFrame(ticks);

  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( Y() < 0) {
  //! Flip the velocity vector
  Y(0);
  setVelocity(-getVelocity());
  }
  if ( Y() > worldHeight-frameHeight) {
  Y(worldHeight - frameHeight);
  setVelocity(-getVelocity());
  }

  if ( X() < 0) {
  X(0);
  setVelocity(-getVelocity());
  if (!keyp && velocityX() > 0)
	  turnRight();
  keyp = false;
  }
  if ( X() > worldWidth-frameWidth) {
  X(worldWidth - frameWidth);
  setVelocity(-getVelocity());
  if (!keyp && velocityX() < 0)
	  turnLeft();
  keyp = false;
  }  
}
