#include <vector>
#include <SDL.h>
#include "ioMod.h"
#include "renderContext.h"
#include "clock.h"
#include "world.h"
#include "viewport.h"

class CollisionStrategy;
class SmartSprite;
class SubjectSprite;

class Engine {
public:
  Engine ();
  ~Engine ();
  void play();

  Engine(const Engine&) = delete;
  Engine& operator=(const Engine&) = delete;
private:
  const RenderContext* rc;
  const IOmod& io;
  Clock& clock;

  SDL_Renderer * const renderer;
  World world;
  Viewport& viewport;

  SubjectSprite* player;
  std::vector<SmartSprite*> sprites;
  std::vector<CollisionStrategy*> strategies;
  int currentStrategy;
  bool collision;

  bool makeVideo;

  void draw() const;
  void update(Uint32);

  void checkForCollisions();
};
