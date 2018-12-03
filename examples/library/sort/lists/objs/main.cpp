#include <iostream>
#include <list>
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
  bool operator<(const Number& rhs) const { return number < rhs.number; }
private:
  int number;
};
std::ostream& operator<<(std::ostream& out, const Number& number) {
  return out << number.getNumber();
}

void init(std::list<Number> & numberList) {
  for (unsigned int i = 0; i < MAX; ++i) {
    numberList.push_back( rand() % MAX_NUMBER );
  }
}

void print(const std::list<Number> & numberList) {
  std::list<Number>::const_iterator ptr = numberList.begin();
  while ( ptr != numberList.end() ) {
    std::cout << (*ptr)  << ", ";
    ++ptr;
  }
  std::cout << std::endl;
}


int main() {
  std::list<Number> numberList;
  init(numberList);
  print(numberList);
  numberList.sort();
  print(numberList);
}
