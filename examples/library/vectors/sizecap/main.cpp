#include <iostream>
#include <vector>

int main() {
  std::vector<int> vec;
  for (unsigned int i = 0; i < 10; ++i) {
    std::cout << vec.size() << ", "<< vec.capacity() << std::endl;
    vec.push_back(i);
  }
}
