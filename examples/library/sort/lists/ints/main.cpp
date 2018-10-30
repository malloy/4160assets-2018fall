#include <iostream>
#include <list>
#include <cstdlib>
const int MAX = 20;
const int MAX_NUMBER = 100;

class High2Low {
public:
  bool operator()(int a, int b) {
    return a>b;
  }
};

void init(std::list<int> & mylist) {
  for (unsigned int i = 0; i < MAX; ++i) {
    mylist.push_back( rand() % MAX_NUMBER );
  }
}

void print(const std::list<int> & mylist) {
  for ( int x : mylist ) {
    std::cout << x  << ", ";
  }
  std::cout << std::endl;
}

int main() {
  std::list<int> mylist;
  init(mylist);
  print(mylist);
  High2Low h;
  mylist.sort( h );
  print(mylist);
}
