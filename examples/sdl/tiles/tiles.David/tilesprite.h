#include <string>
#include <iostream>

#include "drawable.h"
#include "viewport.h"


class TileSprite : public Drawable {
public:
  TileSprite(const std::string& n, const Frame*);
  TileSprite(const std::string& n);
  TileSprite(const TileSprite& s);
  virtual ~TileSprite() { } 
  TileSprite& operator=(const TileSprite&);

  virtual const Frame* getFrame() const { return frame; }
  virtual void setFrame(const Frame* f) { frame = f; }
  virtual void draw() const;
  virtual void update(Uint32);
  unsigned getPixel(Uint32, Uint32) const;

  Vector2f getCenter() const { 
    return Vector2f( X()+frame->getWidth()/2, Y()+frame->getHeight()/2 );
  }
  
  float get_viewX() const { return viewX; }
  float get_viewY() const { return viewY; }
  
private:
  const Frame * frame;
  int frameWidth;
  int frameHeight;
  int worldWidth;
  int worldHeight;
  float viewX;
  float viewY;
  int factor;
  bool demo;
  const Viewport & view;
  int getDistance(const TileSprite*) const;
};











