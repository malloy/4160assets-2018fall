#include <string>
#include <SDL.h>

class FrameGenerator {
public:
  FrameGenerator(SDL_Renderer*, SDL_Window*, int, int, const std::string&);
  void makeFrame();
private:
  SDL_Renderer* const renderer;
  SDL_Window* const window;
  const int WIDTH;
  const int HEIGHT;
  const std::string USERNAME;
  FrameGenerator(const FrameGenerator&);
  FrameGenerator& operator=(const FrameGenerator&);
};
