#include <iostream>
#include <SDL.h>
#include "frameFactory.h"

const int WIDTH = 854;
const int HEIGHT = 480;
const int DELAY = 1000;

class RenderContext{
public:
  static RenderContext* getInstance();
  ~RenderContext();
  SDL_Window* getWindow() const { return window; }
  SDL_Renderer* getRenderer() const { return renderer; }

  Frame* getFrame(const std::string& n) { 
    return factory->getFrame(n);
  }
  std::vector<Frame*> getFrames(const std::string& n) {
    return factory->getFrames(n);
  }
private:
  static RenderContext* instance;
  SDL_Window* window;
  SDL_Renderer* renderer;

  FrameFactory* factory;

  SDL_Window* initWindow();
  SDL_Renderer* initRenderer();
  RenderContext();
  RenderContext(const RenderContext&) = delete;
  RenderContext& operator=(const RenderContext&) = delete;
};
