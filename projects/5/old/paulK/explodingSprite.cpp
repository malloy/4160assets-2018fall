#include <iostream>
#include <cmath>
#include "explodingSprite.h"

BaseExplodingSprite::BaseExplodingSprite(const Sprite& s):
  Sprite(s), chunks(), freeList(), frames()
  {}

BaseExplodingSprite::~BaseExplodingSprite() { 
  for (unsigned int i = 0; i < frames.size(); ++i) {
    delete frames[i];
  }
  chunks.clear();
  freeList.clear();
}

void BaseExplodingSprite::draw() const { 
  // Override draw; use the draw in Chunk, which derives from Sprite.
  // So the draw we're using is actually in Sprite
  std::list<Chunk>::const_iterator ptr = chunks.begin();
  while (ptr != chunks.end()) {
    ptr->draw();
    ++ptr;
  }
}
