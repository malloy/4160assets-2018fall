#include <SDL.h>

#include "gamedata.h"
#include "ioManager.h"
#include "sprite.h"
#include "clock.h"

class Manager {
public:
  Manager ();
  ~Manager ();
  void play();

private:
  bool env;
  Gamedata& gdata;
  IOManager& io;
  Clock& clock;
  SDL_Surface *screen;
  SDL_Surface *orbSurface;
  Frame* orbFrame;
  Sprite* orb;

  void drawBackground() const;
  Manager(const Manager&);
  Manager& operator=(const Manager&);
};
