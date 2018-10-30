#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>
const unsigned int MAX = 10;

void init(std::vector<int>& n) {
  for (unsigned int i = 0; i < MAX; ++i) {
    n.push_back( rand() % 100 );
  }
}

void display(const std::vector<int>& n) {
  for (unsigned int i = 0; i < n.size(); ++i) {
    std::cout << n[i] << ", ";
  }
  std::cout << std::endl;
}

void sort(std::vector<int>& n) {
  bool done = false;
  while ( !done ) {
    done = true;
    for (unsigned int i = 0; i < n.size()-1; ++i) {
      if ( n[i] > n [i+1] ) {
        std::swap(n[i], n[i+1]);
        done = false;
      }
    }
  }
}

int main() {
  std::vector<int> numbers;
  init(numbers);
  display(numbers);
  sort(numbers);
  display(numbers);
}
