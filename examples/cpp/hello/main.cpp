#include <iostream>
int x = 0;

namespace Reza {
  int x = 7;
}

namespace Tyler {
  int x = 99;
}

int main() {
  std::cout << "Reza::x is: " << Reza::x << std::endl;
  std::cout << "Tyler::x is: " << Tyler::x << std::endl;
  std::cout << "::x is: " << ::x << std::endl;
}
