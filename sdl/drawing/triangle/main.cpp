#include <iostream>
#include <SDL2/SDL.h>

const int WIDTH = 640;
const int HEIGHT = 480;

int main (int , char*[]) {
  if ( SDL_Init(SDL_INIT_VIDEO) != 0 ) {
    std::cout << "Failed to initialize SDL2" << std::endl;
    return EXIT_FAILURE;
  }
  SDL_Window* window = SDL_CreateWindow(
      "Drawing a Triangle", SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      WIDTH, HEIGHT, SDL_WINDOW_SHOWN
  );

  SDL_Renderer* renderer = SDL_CreateRenderer( 
    window, -1, SDL_RENDERER_ACCELERATED
  );

  // Set render color to red ( background will be rendered in this color )
  SDL_SetRenderDrawColor( renderer, 208, 209, 210, 255 );

  // Clear window
  SDL_RenderClear( renderer );

  SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
  SDL_RenderDrawLine(renderer, 320, 200, 300, 240);
  SDL_RenderDrawLine(renderer, 300, 240, 340, 240);
  SDL_RenderDrawLine(renderer, 340, 240, 320, 200);
  // The next line does the render:
  SDL_RenderPresent(renderer);

  SDL_Event event;
  const Uint8* keystate;
  while ( true ) {
    keystate = SDL_GetKeyboardState(0);
    if (keystate[SDL_SCANCODE_ESCAPE]) { break; }
    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        break;
      }
    }
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return EXIT_SUCCESS;
}
