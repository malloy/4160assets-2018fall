#ifndef VIEWPORT__H
#define VIEWPORT__H
#include "drawable.h"
#include "gamedata.h"

class Viewport {
public:
  static Viewport& getInstance();
  ~Viewport() { std::cout << "Blocking the view ..." << std::endl; }
  void draw() const;
  void update();

  float X() const { return position[0]; }
  void X(float x) { position[0] = x; }
  float Y() const { return position[1]; }
  void Y(float y) { position[1] = y; }
  float width() const { return viewWidth; }
  void width(float w) { position[0] = w; }
  float height() const { return viewHeight; }
  void height(float h) { position[1] = h; }

  void setObjectToTrack(const Drawable *obj);
  const Drawable* getObjectToTrack() const { return objectToTrack; } 

private:
  Gamedata* const gdata;
  Vector2f position;
  unsigned viewWidth;
  unsigned viewHeight;
  unsigned worldWidth;
  unsigned worldHeight;
  Uint16 objWidth;
  Uint16 objHeight;
  
  const Drawable *objectToTrack;

  Viewport();
  Viewport(const Viewport&);
  Viewport& operator=(const Viewport&);
};
#endif
