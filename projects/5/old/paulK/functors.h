#pragma once
#include <libnoise/noise.h>
#include "vector2f.h"

/*
 * Example functors for ExplodingSprite.
 *
 * The template class ExplodingSprite takes two kinds of functors: one which
 * initializes chunks, and another which accelerates chunks based on their
 * position. We'll refer to them as "chunk initializers" and "chunk updaters".
 * 
 * An initializer implements operator() to accept const reference to the drawable
 * which has exploded, and a reference to the current chunk being initialized.
 * It does not return a value. The referenced chunk may be initialized however
 * seen fit by the author. Some common way to initialize a chunk may be to set the
 * chunk's initial velocity to the exploding drawable.
 *
 * An updater implements operator() to accept a const reference to a Vector2f which
 * is the current position of the chunk being updated. The method returns a Vector2f
 * which the chunk will be accelerated by. An updater ends up being a 2D vector field
 * which is used as the acceleration for all the chunks.
 */

//! Initializer/Updater: accelerates chunks by a constant value or sets velocity to constant value.
class Constant {
public:
  Constant(const Vector2f& v): value(v) {}
  const Vector2f operator()(const Vector2f&) const {
    return value;
  }

  void operator()(const Drawable&, Chunk& chunk) const {
    chunk.setVelocity(value);
  }
private:
  Constant();
  Vector2f value;
};

//! Updater: accelerates chunks according to a perlin noise field.
class Perlin {
public:
  Perlin(double _amp = 1000, double _z1 = 0.0, double _z2 = 1.313):
    perlin1(), perlin2(), amp(_amp), z1(_z1), z2(_z2)
    {}

  const Vector2f operator()(const Vector2f& x) const {
    return amp * Vector2f(
      perlin1.GetValue(x[0], x[1], z1),
      perlin2.GetValue(x[0], x[1], z2)
    );
  }
private:
  noise::module::Perlin perlin1, perlin2;
  double amp, z1, z2;
};

//! Updater: accelerate toward a point.
class Gravitate {
public:
  Gravitate(const Vector2f& pos, float m):
    center(pos), mass(m)
    {}

  const Vector2f operator()(const Vector2f& x) const {
    const Vector2f
      x01 = x - center,
      u01 = x01.normalize();
    return -mass * u01 / x01.magnitude();
  }
private:
  Vector2f center;
  float mass;
};

//! Initializer: initializes chunks to the velocity of the exploding sprite 
class MatchVelocity {
public:
  void operator()(const Drawable& exploder, Chunk& chunk) const {
    chunk.setVelocity(exploder.getVelocity());
  }
private:
};

//! Initializer: chunks travel radially outward from center of exploding sprite.
class RadialVelocity {
public:
  RadialVelocity(float sp = 100): speed(sp) {}
  void operator()(const Drawable& exploder, Chunk& chunk) const {
    const Vector2f
      unit = (chunk.getPosition() - exploder.getCentroid()).normalize();
    chunk.setVelocity(speed * unit);
  }
private:

  float speed;
};
