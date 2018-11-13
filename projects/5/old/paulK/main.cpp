// Brian Malloy        Game Construction

#include "manager.h"

int main(int, char*[]) {
   try {
      Manager game_manager;
      //Game *game = Game::getInstance();
      //game->print();
      game_manager.play();
   }
   catch (const string& msg) { std::cout << msg << std::endl; }
   catch (...) {
      std::cout << "Oops, someone threw an exception!" << std::endl;
   }
   return 0;
}
