#include <string>
#include <iostream>
#include "sprite.h"
#include "bulletPool.h"

class ShootingSprite : public Sprite {
public:
  ShootingSprite(const std::string& n);
  ShootingSprite(const ShootingSprite& s);

  virtual void update(Uint32 ticks);
  virtual void draw() const;
  void shoot();
  virtual bool collidedWith(const Drawable*) const;

private:
  std::string bulletName;
  BulletPool bullets;
  float minSpeed;
  ShootingSprite& operator=(const ShootingSprite&);
};
