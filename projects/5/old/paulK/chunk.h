#include <iostream>
#include "sprite.h"
#include "gamedata.h"

class Chunk : public Sprite {
public:
  explicit Chunk(const Vector2f&, const std::string&, const Frame*);

  virtual void update(Uint32 ticks);

  bool goneTooFar() const { return currentLife > lifetime; }
  void reset() { currentLife = 0; }
  void setLifetime(Uint32 v) { lifetime = v; }

private:
  Uint32 minLife, maxLife, currentLife, lifetime;
};
