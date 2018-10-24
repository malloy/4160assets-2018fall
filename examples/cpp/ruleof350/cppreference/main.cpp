#include <iostream>
#include <cstring>
#include <algorithm>

class string {
  char* cstring; 
  string(const char* s, std::size_t n) : cstring(new char[n]) {
    std::memcpy(cstring, s, n);
  }
 public:
  string(const char* s = "") : string( s, std::strlen(s) + 1 ) { }
  ~string() { delete[] cstring; }
  string(const string& other) : string(other.cstring) {}
  string& operator=(string other) {
    std::swap(cstring, other.cstring);
    return *this;
  }
  const char* getCstring() const { return cstring; }
};

int main() {
  string s("cat"), t("dog");
  t = s;
  std::cout << s.getCstring() << std::endl;
  std::cout << t.getCstring() << std::endl;
  int x = 17, y = 99;

  std::swap(x, y);
  std::cout << "x is: " << x << std::endl;
  std::cout << "y is: " << y << std::endl;
}
