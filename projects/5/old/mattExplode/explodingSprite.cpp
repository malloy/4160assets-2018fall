#include <iostream>
#include <cmath>
#include "explodingSprite.h"

const int DIRECTION_MOD = 100;
const int MAX_EXPLOSION_SPD = 200;
const int MIN_EXPLOSION_SPD = 40;

ExplodingSprite::ExplodingSprite(const Sprite& s) :
  Sprite(s), 
  chunks(), 
  freeList(),
  frames() {
  makeChunks(Gamedata::getInstance()->getXmlInt("orbChunkSize"));
}

ExplodingSprite::~ExplodingSprite() { 
  chunks.clear();
  freeList.clear();
  for ( unsigned int i = 0; i < frames.size(); ++i ) {
    delete frames[i];
  }
}

void ExplodingSprite::draw() const { 
  std::list<Chunk>::const_iterator ptr = chunks.begin();
  while (ptr != chunks.end()) {
    ptr->draw();
    ++ptr;
  }
}


Vector2f ExplodingSprite::getNewVelocity() const {
  // These are used to calculate the direction of the chunk velocity 
  // and have no bearing on its magnitude
  float x_dir = (rand() % DIRECTION_MOD) * (rand()%2?-1:1);
  float y_dir = (rand() % DIRECTION_MOD) * (rand()%2?-1:1);

  // The if statement makes sure we don't try to normalize a Vector2f(0,0) 
  // (which will give a runtime crash)
  if (fabs(x_dir) < 0.001 && fabs(y_dir) < 0.001) {
    x_dir += rand()%2?-1:1;
    y_dir += rand()%2?-1:1;
  }

  // This vector will eventually hold the velocity, 
  // it now holds just the direction:
  Vector2f velocity(x_dir, y_dir);   

  // We normalize to get rid of the magnitude of the above calculations, 
  // but keep direction:
  velocity = velocity.normalize();   

  // Now compute a random speed between MIN_EXPLOSION_SPD and
  // MAX_EXPLOSION_SPD
  int speed = (rand() % (MAX_EXPLOSION_SPD - MIN_EXPLOSION_SPD)) 
              + MIN_EXPLOSION_SPD;

  // We now scale the unit-length direction of velocity by the speed above
  velocity *= speed;

  // velocity is now a random Vector2f in 360 degrees,
  // with magnitude between the min and max speeds.
  return velocity;
}

void ExplodingSprite::update(Uint32 ticks) { 
  std::list<Chunk>::iterator ptr = chunks.begin();
  while (ptr != chunks.end()) {
    ptr->update(ticks);
    if (ptr->goneTooFar()) {
      freeList.push_back(*ptr);
      ptr = chunks.erase(ptr);
    }   
    else ++ptr;
  }
}

void ExplodingSprite::makeChunks(unsigned int n) { 
  unsigned int chunk_width = frame->getWidth()/n;
  unsigned int chunk_height = frame->getHeight()/n;
  Sint16 source_x = frame->getSourceX();
  Sint16 source_y = frame->getSourceY();
  SDL_Surface* spriteSurface(frame->getSurface()); 
  for (unsigned int i = 0; i < n; ++i) {
    for (unsigned int j = 0; j < n; ++j) {
      Frame* frame = 
            new Frame(spriteSurface, chunk_width, chunk_height,
                  source_x+i*chunk_width,  // x coord of surface
                  source_y+j*chunk_height // y coord of surface
                );
      Chunk chunk(
                Vector2f(X()+i*chunk_width,   // x coord of destination 
                         Y()+j*chunk_height), // y coord of destination
                getNewVelocity(),
                getName()+"Chunk",
                frame);
      chunks.push_back(chunk);
      frames.push_back(frame);
    }
  }
}

