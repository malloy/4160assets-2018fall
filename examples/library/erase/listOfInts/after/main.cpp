#include <iostream>
#include <list>
#include <cstdlib>
#include <algorithm>
const int MAX = 20;
const int MAX_NUMBER = 100;

void removeOdds(std::list<int> & mylist) {
  std::list<int>::iterator it = mylist.begin();
  while (it != mylist.end()) {
    if ( *it%2 ) {
      it = mylist.erase(it);
    }
    else ++it;
  }
}

void init(std::list<int> & mylist) {
  for (unsigned int i = 0; i < MAX; ++i) {
    mylist.push_back( rand() % MAX_NUMBER );
  }
}

void print(const std::list<int> & mylist) {
  auto it = mylist.begin();
  while ( it != mylist.end() ) {
    std::cout << (*it)  << ", ";
    ++it;
  }
  std::cout << std::endl;
}

int main() {
  std::list<int> mylist;
  init(mylist);
  print(mylist);
  removeOdds(mylist);
  print(mylist);
}
