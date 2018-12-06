#include <vector>
#include <SDL.h>
#include "menu.h"

class MenuEngine {
public:
  MenuEngine ();
  ~MenuEngine ();
  void play();
  int getOptionChoice() const { return optionChoice; }
  bool starsOptionChosen();
  int getNumStars() const { return numStars; }

private:
  Clock& clock;
  SDL_Renderer * const renderer;
  Menu menu;
  int optionChoice;
  bool starsOption;
  int numStars;

  void draw() const;
  void update(Uint32);

  MenuEngine(const MenuEngine&);
  MenuEngine& operator=(const MenuEngine&);
};
