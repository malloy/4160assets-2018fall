#include <iostream>

class A {
public:
  A(int n) : x(n) {}
  int getX() const { return x; }
private:
  class B;
  int x;
};

class A::B {
public:
  B(int n) : y(n) {}
  int getY() const { return y; }
private:
  int y;
};

int main() {
  int x = 7;
  // A::B x(7);
  std::cout << x << std::endl;
}
