#include <vector>
#include <SDL.h>
#include "ioManager.h"
#include "clock.h"
#include "world.h"
#include "viewport.h"
#include "flockingSystem.h"

class Manager {
public:
  Manager ();
  ~Manager ();
  void play();

private:
  const bool env;
  const IOManager& io;
  Clock& clock;

  SDL_Surface * const screen;
  World world;
  Viewport& viewport;

  int currentSprite;
  FlockingSystem *flock;

  void draw() const;
  void update();

  Manager(const Manager&);
  Manager& operator=(const Manager&);
};
