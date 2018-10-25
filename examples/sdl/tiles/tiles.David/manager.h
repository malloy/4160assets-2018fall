#include <SDL.h>
#include <iostream>
#include <string>
#include <vector>

#include "ioManager.h"
#include "clock.h"
#include "gamedata.h"
#include "sprite.h"
#include "multisprite.h"
#include "multisprite2way.h"
#include "tilesprite.h"
#include "world.h"
#include "viewport.h"


class Manager 
{
public:
  Manager ();
  ~Manager ();
  void play();

private:
  const bool env;
  bool info;
  Sprite infosprite;
  const Gamedata* gdata;
  const IOManager& io;
  Clock& clock;

  SDL_Surface *screen;
  SDL_Surface * const backSurface;
  World world;
  TileSprite tilefloor;
  Viewport& viewport;
  
  void draw() const;
  void update(Uint32);
  Manager(const Manager&);
  Manager& operator=(const Manager&);
};









