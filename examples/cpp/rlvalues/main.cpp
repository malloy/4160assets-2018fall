#include <iostream>

class A{};

A fun() { return A(); }
A fun(A&& a) { 
  std::cout << "r-value reference" << std::endl;
  return A(); 
}
A fun(A& a) { 
  std::cout << "l-value reference" << std::endl;
  return A(); 
}

void f(int&& x) { x = 99; }
void f(int& x) { x = 99; }

int main() {
  int x = 0;
  f(x);
  std::cout << "x is: " << x << std::endl;
}
