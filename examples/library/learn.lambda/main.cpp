#include <iostream>
#include <functional>
#include <ctime>

// Write:
//   (1) maybe neg
//   (2) incr (param to fun)
//   (3) incr (with global)
//   (4) factorial (non recursive)
//   (5) factorial (recursive)

// [capture clause] (parameters) -> return-type {body}

int main() {
  srand( time(0) );
  int x = rand() % 100;
  int z = x;

  std::cout << "x " << x << std::endl;
  x = x*(rand()%2?-1:1);
  std::cout << "x " << x << std::endl;

  auto maybe=[](int& x)->int{ if((x%2)==0)return -1; else return 1;};
  std::cout << "x " << maybe(x) << std::endl;

  auto incr = [](int& x){ return ++x; };
  std::cout << "x " << x << ", " << incr(x) << std::endl;

  std::function<int()> globalincr = [&z]{ return ++z; };
  std::cout << "z " << x << ", " << globalincr() << std::endl;

  auto factorial = [](int x)->int{
    int f = 1;
    for (int i = 2; i <=x; ++i) f *= i;
    return f;
  };
  std::cout << "factorial(5) = " << factorial(5) << std::endl;

  std::function<int(int)> fact;
  fact = [&fact](int x) { if(x==1) return 1; else return x*fact(x-1);};
  std::cout << "fact(5) = " << fact(5) << std::endl;
}
