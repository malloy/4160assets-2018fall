#include <iostream>
#include "world.h"
#include "renderContext.h"

World::World(const std::string& name, int fact) : 
  image( RenderContext::getInstance()->getImage(name) ),
  factor(fact),
    worldHeight( Gamedata::getInstance().getXmlInt("world/height") ),
    imageHeight( image->getHeight() ),
    viewX(0.0), viewY(0.0), 
    view(Viewport::getInstance()) 
{ }

void World::update() {
  viewY = static_cast<int>(view.getY() / factor) % imageHeight;
  viewX = view.getX();
}

void World::draw() const { 
  image->draw(0,0,-viewX,-viewY);
  image->draw(0,0,-viewX,imageHeight-viewY);
}

