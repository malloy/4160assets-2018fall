#include <iostream>
#include <list>
#include <cstdlib>
#include <ctime>
#include <algorithm>
const int MAX = 20;

class Number {
public:
  Number() : number(0) { }
  explicit Number(int n) : number(n) { }
  Number(const Number& a) : number(a.number) { }
  int getNumber() const { return number; }
  bool operator<(const Number& rhs) const { return number < rhs.number; }
private:
  int number;
};
std::ostream& operator<<(std::ostream& out, const Number* number) {
  return out << number->getNumber();
}

class Target{
public:
  Target( int n ) : number(n) {}
  bool operator()(const Number* rhs) const {
    return number == rhs->getNumber();
  }
private:
  int  number;
};

void init(std::list<Number*> & numberList) {
  for (unsigned int i = 0; i < MAX; ++i) {
    numberList.push_back( new Number(i) );
  }
}

void print(const std::list<Number*> & numberList) {
  for ( const Number* n : numberList ) {
    std::cout << n  << ", ";
  }
  std::cout << std::endl;
}

int main() {
  srand( time(0) );
  std::list<Number*> numberList;
  init(numberList);
  print(numberList);

  std::list<Number*>::iterator it = 
    find_if( numberList.begin(), numberList.end(), Target(rand()%50) );

  if (  it == numberList.end() ) std::cout << "NO" << std::endl;
  else std::cout << "YES" << std::endl;

}
