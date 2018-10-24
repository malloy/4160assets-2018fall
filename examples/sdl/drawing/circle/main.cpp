#include <SDL2/SDL.h>

const int NO_OF_POINTS = 360;
const double PI = 3.1415926535897;
const double RAD2DEG = (180/PI);
const double DEG2RAD = (PI/180);
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

const SDL_Color RED = {255, 0, 0, 255};

double DegToRad(double x) {
  return x*DEG2RAD;
}
double RadToDeg(double x) {
  return x*RAD2DEG;
}

int main(void) {
  SDL_Renderer *renderer;
  SDL_Window *window;

  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer(
    WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer
  );

  SDL_SetRenderDrawColor( renderer, 208, 209, 210, 255 );
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, RED.r, RED.g, RED.b, RED.a);

  SDL_Point center = {320, 240};
  int radius = 50;

  int step = 360/NO_OF_POINTS;
  for (int theta = 0; theta < 360; theta += step) {
    SDL_RenderDrawPoint(renderer, 
      center.x+radius*cos(DegToRad(theta)), 
      center.y+radius*sin(DegToRad(theta))
    );
  }


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
