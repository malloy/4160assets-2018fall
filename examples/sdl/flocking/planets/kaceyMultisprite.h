#ifndef TWOWAYMULTISPRITE__H
#define TWOWAYMULTISPRITE__H

#include <string>
#include <iostream>
#include <vector>
using std::string;

#include "drawable.h"
class KaceyMultisprite : public Drawable {
public:
  KaceyMultisprite(const string&);
  KaceyMultisprite(const string&, const Vector2f& posoffset, 
                    const Vector2f& veloffset);

  KaceyMultisprite(const std::string&, const Vector2f& pos, 
                    const Vector2f& vel, const std::vector<Frame*>& fms);

  KaceyMultisprite(const KaceyMultisprite&);
  virtual ~KaceyMultisprite() { } 

  const std::string& getType() const {return type;}
  virtual void draw() const;
  virtual void update(Uint32 ticks);
  void turnRight();
  void turnLeft();
  virtual const Frame* getFrame() const { 
    return frames[currentFrame]; 
  }
protected:
  const std::string type;
  const std::vector<Frame *> frames;
  int worldWidth;
  int worldHeight;
  float dt;
  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  float timeSinceLastFrame;
  int frameWidth;
  int frameHeight;
  float flipx;
  void advanceFrame(Uint32 ticks);
  bool keyp;
};
#endif
