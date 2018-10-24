#include <iostream>
#include <cstring>

class string {
public:
  string() : buf(new char[1]) {
    buf[0] = '\0';
  }
  string(const char* s) : buf(new char[strlen(s)+1]) {
    strcpy(buf, s);
  }
  string(const string& s) : buf(new char[strlen(s.buf)+1]) {
    strcpy(buf, s.buf);
  }
  ~string() { delete [] buf; }

  const char* getBuf() const { return buf; }
  void setBuf(const char* b) {
    if ( b == nullptr ) {
      delete [] buf;
      buf = new char[1];
      buf[0] = '\0';
      return;
    }
    delete [] buf;
    buf = new char[strlen(b)+1];
    strcpy(buf, b);
  }

  string& operator=(const string& rhs) {
    if ( this == &rhs ) return *this;
    delete [] buf;
    buf = new char[strlen(rhs.buf)+1];
    strcpy(buf, rhs.buf);
    return *this;
  }
private:
  char* buf;
};
std::ostream& operator<<(std::ostream& out, const string& s) {
  return out << s.getBuf();
}

int main() {
  string cat("cat"), dog(cat);
  dog = cat;
  std::cout << cat << dog << std::endl;

}
