#include <iostream>
#include <functional>
#include <list>
#include <cstdlib>
#include <algorithm>
const int MAX = 20;
const int MAX_NUMBER = 100;

// [capture clause] (parameters) -> return-type {body}

class Number {
public:
  Number() : number(0) { }
  Number(int n) : number(n) {
  }
  Number(const Number& a) : number(a.number) { }
  int getNumber() const { return number; }
  bool operator<(const Number& rhs) const { return number < rhs.number; }
  bool operator>(const Number& rhs) const { return number > rhs.number; }
private:
  int number;
};
std::ostream& operator<<(std::ostream& out, const Number* number) {
  return out << number->getNumber();
}

void init(std::list<Number*> & numberList) {
  for (unsigned int i = 0; i < MAX; ++i) {
    numberList.push_back( new Number(rand() % MAX_NUMBER) );
  }
}
void print(const std::list<Number*> & numberList) {
  for ( const Number* number : numberList ) {
    std::cout << number  << ", ";
  }
  std::cout << std::endl;
}

bool greater(const Number* a, const Number* b) {
  return (*a) > (*b);
}
bool lesser(const Number* a, const Number* b) {
  return (*a) < (*b);
}

int main() {
  std::list<Number*> numberList;
  init(numberList);
  print(numberList);

  numberList.sort( greater );
  print(numberList);

  numberList.sort( 
    [](const Number* a, const Number* b)->bool{return (*a) < (*b);} 
  );
  print(numberList);
}
