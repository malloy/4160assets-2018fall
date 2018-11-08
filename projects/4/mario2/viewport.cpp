#include <sstream>
#include "viewport.h"
#include "ioMod.h"

Viewport& Viewport::getInstance() {
  static Viewport viewport;
  return viewport;
}

Viewport::Viewport() : 
  gdata(Gamedata::getInstance()),
  msgPos(
    Vector2f( gdata.getXmlInt("view/loc/x"), gdata.getXmlInt("view/loc/y") )
  ),
  viewPos(0, 0),
  worldWidth(gdata.getXmlInt("world/width")),
  worldHeight(gdata.getXmlInt("world/height")),
  viewWidth(gdata.getXmlInt("view/width")), 
  viewHeight(gdata.getXmlInt("view/height")),

  player(gdata.getXmlStr("player")),
  playerWidth(player.getScaledWidth()), 
  playerHeight(player.getScaledHeight()),
  playerPos(viewWidth/2, viewHeight-playerWidth),
  playerVel( player.getVelocity() ),
  initPlayerVel(playerVel)
{}

void Viewport::right() { 
 playerVel[0] = initPlayerVel[0];
} 
void Viewport::left()  { 
 playerVel[0] = -initPlayerVel[0];
} 

void Viewport::up()    { 
  playerVel[1] = -initPlayerVel[1];
} 
void Viewport::down()  { 
  playerVel[1] = initPlayerVel[1];
}

void Viewport::stop() { 
  //player.setVelocity( Vector2f(0, 0) );
  playerVel[0] = 0.93*playerVel[0];
  playerVel[1] = 0.0;
}


void Viewport::draw() const {
  player.draw();
}

void Viewport::update(Uint32 ticks) {
  Vector2f incr = playerVel * static_cast<float>(ticks) * 0.001;
  viewPos = viewPos + incr;
  playerPos = viewPos;
  playerPos[0] += viewWidth/2;
  playerPos[1] += viewHeight-playerHeight;

  if (viewPos[0] < 0) { viewPos[0] = 0; }

  if (viewPos[0] > (worldWidth - viewWidth)) {
    viewPos[0] = worldWidth-viewWidth;
  }

  if (viewPos[1] < 0) { viewPos[1] = 0; }
  if (viewPos[1] > (worldHeight - viewHeight)) {
    viewPos[1] = worldHeight-viewHeight;
  }
  player.setPosition( playerPos );
  player.advanceFrame( ticks );
  stop();
}
