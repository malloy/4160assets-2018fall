#ifndef SINGLE__H
#define SINGLE__H
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <string>
#include <sstream>
using std::string;

const int DEFAULT_FONT_SIZE = 20;

const Uint16 WIDTH = 640;
const Uint16 HEIGHT = 480;
const unsigned int MAX_STRING = 50;

class IOManager {
public:
  static IOManager* getInstance();
  SDL_Surface * getScreen() const { return screen; }
  ~IOManager() { 
    TTF_CloseFont(font);
    SDL_FreeSurface(screen);
  }
  SDL_Surface* loadAndSet(const char* filename, bool setcolorkey) const;

  void printMessageAt(const string& msg, Uint32 x, Uint32 y) const;
  void printMessageCenteredAt(const string& msg, Uint32 y) const;
  void printMessageValueAt(const string& msg, float value, 
         Uint32 x, Uint32 y) const;
  void printStringAfterMessage(const string&, Uint32 x, Uint32 y) const;

  void buildString(SDL_Event);
  void clearString() { inputString = ""; }
  const string& getString() const { return inputString; }
private:
  IOManager();
  IOManager(const IOManager&);
  IOManager& operator=(const IOManager&);

  SDL_Surface * screen;
  static IOManager* instance;
  TTF_Font *font;
  string inputString;
};
#endif
