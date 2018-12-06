#include <vector>
#include <SDL.h>
#include "renderContext.h"
#include "world.h"
#include "viewport.h"
#include "menuEngine.h"

class Engine {
public:
  Engine ();
  ~Engine ();
  void play();
  void switchSprite();

private:
  const RenderContext* rc;
  const IOmod& io;
  Clock& clock;

  SDL_Renderer * const renderer;
  MenuEngine menuEngine;
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
