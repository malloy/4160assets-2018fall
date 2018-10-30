#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstdlib>
const unsigned int MAX = 10;

class Number {
public:
  Number(int n) : number(n) {}
  int getNumber() const { return number; }
  void setNumber(int n) { number = n; }
private:
  int number;
};
class CompareGreater {
public:
  bool operator()(const Number* lhs, const Number* rhs) const {
    return lhs->getNumber() > rhs->getNumber();
  }
};

void init(std::vector<Number*>& n) {
  for (unsigned int i = 0; i < MAX; ++i) {
    n.push_back( new Number(rand() % 100) );
  }
}

void display(const std::vector<Number*>& n) {
  for (unsigned int i = 0; i < n.size(); ++i) {
    std::cout << n[i]->getNumber() << ", ";
  }
  std::cout << std::endl;
}

template<typename T, typename U>
void sort(std::vector<T>& n, const U& cg) {
  bool done = false;
  while ( !done ) {
    done = true;
    for (unsigned int i = 0; i < n.size()-1; ++i) {
      if ( cg(n[i], n[i+1]) ) {
        std::swap(n[i], n[i+1]);
        done = false;
      }
    }
  }
}

int main() {
  std::vector<Number*> numbers;
  init(numbers);
  display(numbers);
  sort(numbers, CompareGreater());
  display(numbers);
}
