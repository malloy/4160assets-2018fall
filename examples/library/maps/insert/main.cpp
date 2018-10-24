#include <iostream>
#include <cstdlib>
#include <map>

void print(const std::map<std::string, int>& mymap) {
  std::cout << "size: " << mymap.size() << std::endl;
  for ( const auto& x : mymap ) {
    std::cout << x.first << ", " << x.second << std::endl;
  }
}

int main() {
  std::map<std::string, int> mymap;
  std::pair<std::string, int> dog("dog", 99);
  mymap.insert( dog );

  mymap["cat"] = 17;
  mymap["cat"] = 18;
  std::cout << mymap["antelope"] << std::endl;
  std::cout << mymap["Antelope"] << std::endl;

  mymap.insert({"bear", 88});
  mymap.emplace("Bear", 77); 
  print( mymap );
  mymap.erase("antelope");
  print( mymap );
}
