#include <iostream>
#include <cmath>
#include "chunk.h"

Chunk::Chunk(const Vector2f& pos, const string& name, const Frame* fm) :
  Sprite(name, pos, Vector2f(0,0), fm),
  minLife(Gamedata::getInstance().getXmlInt(name+"MinLife")),
  maxLife(Gamedata::getInstance().getXmlInt(name+"MaxLife")),
  currentLife(0),
  lifetime(Gamedata::getInstance().getRandInRange(minLife, maxLife))
{ }

void Chunk::update(Uint32 ticks) { 
  setPosition(getPosition() + getVelocity() * ticks * 0.001f);
  currentLife += ticks;
}

