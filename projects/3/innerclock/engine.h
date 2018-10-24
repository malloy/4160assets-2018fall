#pragma once
#include <vector>
#include <SDL.h>
#include "ioMod.h"
#include "renderContext.h"
#include "world.h"
#include "viewport.h"

class Engine {
public:
  Engine ();
  ~Engine ();
  void play();
  void switchSprite();

private:
  class Clock;
  const RenderContext* rc;
  const IoMod& io;
  Clock& clock;

  SDL_Renderer * const renderer;
  World world;
  Viewport& viewport;

  Drawable* star;
  Drawable* spinningStar;
  int currentSprite;

  bool makeVideo;

  void draw() const;
  void update(Uint32);

  Engine(const Engine&);
  Engine& operator=(const Engine&);
  void printScales() const;
  void checkForCollisions();
};
