#ifndef VIEWPORT__H
#define VIEWPORT__H
#include "multisprite.h"
#include "gameData.h"

class Viewport {
public:
  static Viewport& getInstance();
  void draw() const;
  void update(Uint32);

  Vector2f getPosition() const { return viewPos; }
  float getX() const  { return viewPos[0]; }
  void  setX(float x) { viewPos[0] = x; }
  float getY() const  { return viewPos[1]; }
  void  setY(float y) { viewPos[1] = y; }

  void right();
  void left();
  void up();
  void down();
  void stop();

private:
  const Gamedata& gdata;
  Vector2f msgPos;
  Vector2f viewPos;
  int worldWidth;
  int worldHeight;
  int viewWidth;
  int viewHeight;

  MultiSprite player;
  int playerWidth;
  int playerHeight;
  Vector2f playerPos;
  Vector2f playerVel;
  Vector2f initPlayerVel;
  
  Viewport();
  Viewport(const Viewport&);
  Viewport& operator=(const Viewport&);
};
#endif
