#ifndef SPRITE__H
#define SPRITE__H
#include <string>
#include "drawable.h"

class Sprite : public Drawable {
public:
  Sprite(const std::string&);
  Sprite(const Sprite&);
  virtual ~Sprite() { } 
  Sprite& operator=(const Sprite&);

  virtual const Frame* getFrame() const { return frame; }
  virtual void draw() const;
  virtual void update(Uint32 ticks);

private:
  Frame * frame;
  int worldWidth;
  int worldHeight;

  int getDistance(const Sprite*) const;
  Vector2f makeVelocity(int, int) const;
};
#endif
