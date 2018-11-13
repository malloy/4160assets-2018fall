#ifndef SPRITE__H
#define SPRITE__H

#include <string>
#include <iostream>
#include "drawable.h"

class Sprite : public Drawable {
public:
  // In this version, frame is a parameter:
  Sprite(const std::string&, const Frame* const);  

  // The next constructor is for a constructor in Chunks because it
  // must set pos and vel based on the exploding sprite's pos and vel
  Sprite(const std::string&, const Vector2f& pos, const Vector2f& vel,
         const Frame*);

  Sprite(const Sprite& s); // canonical form
  virtual ~Sprite() { }  // Don't delete frame; manager will reuse it 

  // Check out the implementation
  Sprite& operator=(const Sprite&); // canonical form

  virtual void draw() const;
  virtual void update(Uint32 ticks);
  virtual const Frame* getFrame() const { return frame; }

private:
  const Frame * frame;
  int frameWidth;
  int frameHeight;
  int worldWidth;
  int worldHeight;
  int getDistance(const Sprite*) const;
};
#endif
