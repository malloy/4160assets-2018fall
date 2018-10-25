// Brian Malloy        Game Construction

#include "manager.h"
Gamedata* Gamedata::instance;

int main(int, char*[]) {
   try {
      Manager game_manager;
      game_manager.play();
   }
   catch (const string& msg) { std::cout << msg << std::endl; }
   catch (...) {
      std::cout << "Oops, someone threw an exception!" << std::endl;
   }
   return 0;
}
