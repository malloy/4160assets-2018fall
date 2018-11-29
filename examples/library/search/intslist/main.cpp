#include <iostream>
#include <list>
#include <cstdlib>
#include <ctime>
#include <algorithm>
const int MAX = 20;
const int MAX_NUMBER = 100;

void init(std::list<int> & vec) {
  for (unsigned int i = 0; i < MAX; ++i) {
    vec.push_back( rand() % MAX_NUMBER );
  }
}

// Can we use a ranged for loop in print?
void print(const std::list<int> & vec) {
  std::list<int>::const_iterator ptr = vec.begin();
  while ( ptr != vec.end() ) {
    std::cout << (*ptr)  << ", ";
    ++ptr;
  }
  std::cout << std::endl;
}

int main() {
  srand( time(0) );
  std::list<int> vec;
  init(vec);
  print(vec);
  int number = rand()%MAX_NUMBER;
  const auto& it = find(vec.begin(), vec.end(), number);
  if ( it == vec.end() ) {
    std::cout << number << " not found" << std::endl;
  }
  else {
    std::cout << number << " found" << std::endl;
  }
}
