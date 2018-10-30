#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
const int MAX = 20;
const int MAX_NUMBER = 100;

class Number {
public:
  Number() : number(0) { }
  Number(int n) : number(n) { }
  Number(const Number& a) : number(a.number) { }
  int getNumber() const { return number; }
private:
  int number;
};
std::ostream& operator<<(std::ostream& out, const Number* number) {
  return out << number->getNumber();
}

class NumberLess{
public:
  bool operator()(const Number* const lhs, const Number* const rhs) const {
    return lhs->getNumber() > rhs->getNumber();
  }
};

void init(std::vector<Number*> & vec) {
  vec.reserve(MAX);
  for (unsigned int i = 0; i < MAX; ++i) {
    vec.push_back( new Number(rand() % MAX_NUMBER) );
  }
}

void print(const std::vector<Number*> & vec) {
  for ( Number* n : vec ) {
    std::cout << n->getNumber()  << ", ";
  }
  std::cout << std::endl;
}

int main() {
  std::vector<Number*> vec;
  init(vec);
  print(vec);
  std::sort(vec.begin(), vec.end(), NumberLess());
  print(vec);
}
