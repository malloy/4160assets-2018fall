#include <iostream>
#include <cstring>

class string {
public:
  string() : buf(new char[1]) {
    buf[0] = '\0';
  }
  string(const char* s) : buf(new char[strlen(s)+1]) {
    std::cout << "CONVERSION" << std::endl;
    strcpy(buf, s);
  }
  const char* getBuf() const { return buf; }

  // Rule of 3:
  string(const string& s) : buf(new char[strlen(s.buf)+1]) {
    strcpy(buf, s.buf);
  }
  ~string() { 
    delete [] buf; 
  }  // s/ destructors always be virtual
  string& operator=(const string& rhs) {
    if ( this == &rhs ) return *this;
    delete [] buf;
    buf = new char[strlen(rhs.buf)+1];
    strcpy(buf, rhs.buf);
    return *this;
  }

  // Rule of 5:
  string(string&& s) : buf(std::move(s.buf)) {
    s.buf = nullptr;
  }
  string& operator=(string&& rhs) {
    std::cout << "MOVE ASSIGNMENT" << std::endl;
    //delete [] buf;
    //buf = (rhs.buf);
    //rhs.buf = nullptr;
    std::swap(buf, rhs.buf);
    return *this;
  }
private:
  char* buf;
};
std::ostream& operator<<(std::ostream& out, const string& s) {
  return out << s.getBuf();
}

int main() {
  string dog;
  dog = "dog";
  std::cout << dog << std::endl;
}
