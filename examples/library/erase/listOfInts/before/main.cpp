#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
const int MAX = 20;
const int MAX_NUMBER = 100;

void init(std::vector<int> & vec) {
  for (unsigned int i = 0; i < MAX; ++i) {
    vec.push_back( rand() % MAX_NUMBER );
  }
}

void print(const std::vector<int> & vec) {
  for ( const int x : vec ) {
    std::cout << x  << ", ";
  }
  std::cout << std::endl;
}

int main() {
  std::vector<int> vec;
  init(vec);
  print(vec);
  //removeOdds(vec);
  //print(vec);
}
