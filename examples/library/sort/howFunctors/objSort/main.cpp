#include <iostream>
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

void sort(std::vector<Number*>& n, const CompareGreater& cl) {
  bool done = false;
  while ( !done ) {
    done = true;
    for (unsigned int i = 0; i < n.size()-1; ++i) {
      if ( cl(n[i], n[i+1]) ) {
        int t = n[i]->getNumber();
        n[i]->setNumber(n[i+1]->getNumber());
        n[i+1]->setNumber(t);
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
