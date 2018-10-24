#ifndef PLAYER__H
#define PLAYER__H
#include <SDL.h>
#include <string>
#include <vector>
#include <cmath>

#include "multisprite.h"

class Player {
public:
  Player(const std::string&);
  Player(const Player&);

  void draw() const { player.draw(); }
  void update(Uint32 ticks);
  const MultiSprite* getPlayer() const { return &player; }

  const std::string& getName() const { return player.getName(); }
  int getX() const { return player.getX(); }
  int getY() const { return player.getY(); }
  const Image* getImage() const { 
    return player.getImage();
  }
  int getScaledWidth()  const { 
    return player.getScaledWidth();
  } 
  int getScaledHeight()  const { 
    return player.getScaledHeight();
  } 
  const SDL_Surface* getSurface() const { 
    return player.getSurface();
  }

  void right();
  void left();
  void up();
  void down();
  void stop();

  Player& operator=(const Player&) = delete;

private:
  MultiSprite player;
  Vector2f initialVelocity;
  int worldWidth;
  int worldHeight;
};
#endif
