#include "drawFilledTriangle.h"

DrawFilledTriangle::DrawFilledTriangle(SDL_Window* w, SDL_Renderer* r, 
                  const Vector2f& x, const Vector2f& y, const Vector2f& z) 
  : window(w), renderer(r), v0(x), v1(y), v2(z) {}                     

void DrawFilledTriangle::draw() const {
  float x = smallest(v0[0],v1[0],v2[0]);
  float y = smallest(v0[1],v1[1],v2[1]);
  Vector2f box0( x, y ); 
  std::cout << "box0: " << box0 << std::endl;

  x = largest(v0[0],v1[0],v2[0]);
  y = largest(v0[1],v1[1],v2[1]);
  Vector2f box1( x, y ); 
  std::cout << "box1: " << box1 << std::endl;

  for (int x = box0[0]; x <= box1[0]; ++x) {
    for (int y = box0[1]; y <= box1[1]; ++y) {
      Vector2f p(x, y);
      if ( triangle(p, 0.6) ) {
        SDL_RenderDrawPoint(renderer, x, y);
      }
    }
  }
}

float DrawFilledTriangle::wedge(Vector2f a, Vector2f b) const {
 return a[0]*b[1] - a[1]*b[0];
}

float DrawFilledTriangle::triangle(Vector2f x, float fuzz) const {
  Vector2f e0 = v1 - v0;
  Vector2f e1 = v2 - v1;
  Vector2f e2 = v0 - v2;
  float N = wedge(e1, -e0);
  if(N <= -0.00001){
      N  *= -1.0;
      e0 *= -1.0;
      e1 *= -1.0;
      e2 *= -1.0;
  }

  float b0 = wedge(e0, x - v0);
  if(b0 <= -0.00001) { return 0.0; }
  float b1 = wedge(e1, x - v1);
  if(b1 <= -0.00001) { return 0.0; }
  float b2 = wedge(e2, x - v2);
  if(b2 <= -0.00001) { return 0.0; }
  if(fuzz == 0.0) return 1.0;
  return std::min(1.0, (pow(b0*b1*b2, 0.33) * 3.0 / N) / fuzz);
}

int DrawFilledTriangle::smallest(int a, int b, int c) const {
  int temp = std::min(a, b);
  return std::min(temp, c);
}
int DrawFilledTriangle::largest(int a, int b, int c) const {
  int temp = std::max(a, b);
  return std::max(temp, c);
}

