#include <iostream>
#include <string>
#include <sstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

const int WIDTH = 640;
const int HEIGHT = 480;
const std::string TITLE = "Drawing a Rectangle";
const std::pair<int, int> CORNER(150, 150);

void printMouseInfo(int x, int y, TTF_Font* font, SDL_Renderer* renderer) {
  std::stringstream strm; 
  strm << '(' << x << ", " << y  << ')' << std::ends;
  std::string msg = strm.str();
  SDL_Color textColor = {0, 0, 255, 0};
  SDL_Surface* surface = 
    TTF_RenderText_Solid(font, msg.c_str(), textColor);

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

  int width = surface->w;
  int height = surface->h;
  SDL_FreeSurface(surface);
  SDL_Rect dst = {CORNER.first+10, CORNER.second+10, width, height};

  SDL_RenderCopy(renderer, texture, NULL, &dst);
  SDL_DestroyTexture(texture);
}

void drawRectangles(SDL_Renderer* renderer) {
  // Set render color to red ( background will be rendered in this color )
  SDL_SetRenderDrawColor( renderer, 208, 209, 210, 255 );
  SDL_RenderClear( renderer );
  SDL_Rect r = {150, 150, 250, 150};
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255/2 );
  SDL_RenderFillRect( renderer, &r );
  SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255/2 );
  SDL_RenderDrawRect( renderer, &r );
}

int main (int , char*[]) {
  try {
    if ( SDL_Init(SDL_INIT_VIDEO) != 0 ) {
      throw "Failed to initialize SDL2";
    }
    SDL_Window* window = SDL_CreateWindow(
      TITLE.c_str(), 
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      WIDTH,
      HEIGHT,
      SDL_WINDOW_SHOWN
    );

    SDL_Renderer* renderer = SDL_CreateRenderer( 
      window, -1, SDL_RENDERER_ACCELERATED
    );
    TTF_Init();
    TTF_Font *font = TTF_OpenFont("fonts/FreeSerifBold.ttf", 24);
    if ( font == NULL ) {
      throw std::string("TTF_OpenFont failed: ") + TTF_GetError();
    }

    SDL_Event event;
    const Uint8* keystate;
    int x = -1, y = -1;
    while ( true ) {
      keystate = SDL_GetKeyboardState(0);
      if (keystate[SDL_SCANCODE_ESCAPE]) { break; }
      if (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
          break;
        }
        else if( event.type == SDL_MOUSEMOTION ) {
          SDL_GetMouseState(&x, &y);
        }
      }
      drawRectangles(renderer);
      printMouseInfo(x, y, font, renderer);
      SDL_RenderPresent(renderer);
    }
  
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
  
    return EXIT_SUCCESS;
  }
  catch( std::string& msg ) {
    std::cout << msg << std::endl;
  }
}
