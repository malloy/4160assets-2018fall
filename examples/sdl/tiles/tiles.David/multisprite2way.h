#ifndef MULTISPRITE2WAY__H
#define MULTISPRITE2WAY__H

#include <string>
#include <iostream>
#include <vector>

#include "drawable.h"

class MultiframeSprite2Way : public Drawable {
public:
  MultiframeSprite2Way(const std::string& n, const std::vector<Frame*>& fms);
  MultiframeSprite2Way(const std::string& n);
  MultiframeSprite2Way(const MultiframeSprite2Way& s);
  virtual ~MultiframeSprite2Way() { } 
  virtual const Frame* getFrame() const { return frames[currentFrame]; }

  virtual void draw() const;
  virtual void update(Uint32 ticks);

private:
  const std::vector<Frame *> frames;
  int frameWidth;
  int frameHeight;
  int worldWidth;
  int worldHeight;
  float dt;
  unsigned currentFrame;
  unsigned currentLayer;
  unsigned numberOfFrames;
  unsigned frameInterval;
  void advanceFrame(Uint32 ticks);
};
#endif
