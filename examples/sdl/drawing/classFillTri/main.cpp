#include <iostream>
#include <SDL2/SDL.h>
#include "drawFilledTriangle.h"

const int WIDTH = 640;
const int HEIGHT = 480;

Vector2f v0(320, 100);
Vector2f v1(270, 186);
Vector2f v2(370, 186);

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

  // Background will be rendered in this color:
  SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );

  // Clear window
  SDL_RenderClear( renderer );

  SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );
  DrawFilledTriangle triangle(window, renderer, v0, v1, v2);
  triangle.draw();

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
