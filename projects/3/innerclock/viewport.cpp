#include <sstream>
#include "viewport.h"
#include "ioMod.h"

Viewport& Viewport::getInstance() {
  static Viewport viewport;
  return viewport;
}

Viewport::Viewport() : 
  gdata(Gamedata::getInstance()),
  viewPos(0, 0),
  msgPos(
    Vector2f( gdata.getXmlInt("view/loc/x"), gdata.getXmlInt("view/loc/y") )
  ),
  worldWidth(gdata.getXmlInt("world/width")),
  worldHeight(gdata.getXmlInt("world/height")),
  viewWidth(gdata.getXmlInt("view/width")), 
  viewHeight(gdata.getXmlInt("view/height")),
  objWidth(0), objHeight(0),
  objectToTrack(NULL) 
{}

void Viewport::setObjectToTrack(const Drawable *obj) { 
  objectToTrack = obj; 
  objWidth = objectToTrack->getScaledWidth();
  objHeight = objectToTrack->getScaledHeight();
}

void Viewport::draw() const {
  IoMod::getInstance().
    writeText("Tracking: "+objectToTrack->getName(), msgPos[0], msgPos[1]);
}

void Viewport::update() {
  const float x = objectToTrack->getX();
  const float y = objectToTrack->getY();

  viewPos[0] = (x + objWidth/2) - viewWidth/2;
  viewPos[1] = (y + objHeight/2) - viewHeight/2;
  if (viewPos[0] < 0) viewPos[0] = 0;
  if (viewPos[1] < 0) viewPos[1] = 0;
  if (viewPos[0] > (worldWidth - viewWidth)) {
    viewPos[0] = worldWidth-viewWidth;
  }
  if (viewPos[1] > (worldHeight - viewHeight)) {
    viewPos[1] = worldHeight-viewHeight;
  }
}
