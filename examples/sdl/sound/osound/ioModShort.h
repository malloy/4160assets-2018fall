#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

class IOmod {
public:
  static IOmod& getInstance();
  ~IOmod();
  SDL_Texture* readTexture(const std::string& filename);
  SDL_Surface* readSurface(const std::string& filename);
  void setRenderer(SDL_Renderer* r) { renderer = r; }
  void writeText(const std::string&, int, int) const;
private:
  int init;
  TTF_Font* font;
  SDL_Color textColor;
  SDL_Renderer* renderer;
  IOmod();
  IOmod(const IOmod&);
  IOmod& operator=(const IOmod&);
};
