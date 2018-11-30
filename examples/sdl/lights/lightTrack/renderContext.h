#include <iostream>
#include <SDL.h>
#include "imageFactory.h"

// These global constants should be eliminated; they
// should be read from xmlSpec/game.xml

class RenderContext{
public:
  static RenderContext* getInstance();
  ~RenderContext();
  SDL_Window* getWindow() const { return window; }
  SDL_Renderer* getRenderer() const { return renderer; }

  Image* getImage(const std::string& n) { 
    return factory->getImage(n);
  }
  std::vector<Image*> getImages(const std::string& n) {
    return factory->getImages(n);
  }
private:
  static RenderContext* instance;
  SDL_Window* window;
  SDL_Renderer* renderer;

  ImageFactory* factory;

  SDL_Window* initWindow();
  SDL_Renderer* initRenderer();
  RenderContext();
  RenderContext(const RenderContext&) = delete;
  RenderContext& operator=(const RenderContext&) = delete;
};
