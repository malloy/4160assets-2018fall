#include <iostream>
#include <vector>
#include <cstring>

class string {
public:
  string() : buf(new char[1]) { 
    buf[0] = '\0';
    std::cout << "default" << std::endl;
  }
  string(const char * b) : buf(new char[strlen(b)+1]) {
    strcpy(buf, b);
    std::cout << "convert" << std::endl;
  }
  string(const string & s) : buf(new char[strlen(s.buf)]) {
    strcpy(buf, s.buf);
    std::cout << "copy" << std::endl;
  }
  string(string && s) : buf(s.buf) {
    s.buf = nullptr;
    std::cout << "move constructor" << std::endl;
  }
  ~string() { 
    delete [] buf;
    std::cout << "destructor string" << std::endl;
  }

  const char* getBuf() const { return buf; }

  string& operator=(const string& rhs) {
    std::cout << "copy assign" << std::endl;
    delete [] buf;
    buf = new char[strlen(rhs.buf)+1];
    strcpy(buf, rhs.buf);
    return *this;
  }
private:
  char *buf;
};
std::ostream& operator<<(std::ostream& out, const string& n) {
  return out << n.getBuf();
}

int main() {
  std::vector<string> mon;
  //mon.emplace_back("mewtwo");
   mon.push_back("mewtwo");
}
