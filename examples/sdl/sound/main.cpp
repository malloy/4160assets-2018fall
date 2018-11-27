#include <iostream>
#include <SDL.h>
#include "sound.h"
#include "ioModShort.h"

// To run this demo you will need to install SDL2_mixer
// Notice the flag in the Makefile, which you also must add

const int WIDTH = 859;
const int HEIGHT = 480;
const int DELAY = 1000;

SDL_Window* initWindow( ) {
	SDL_Window* window = 
    SDL_CreateWindow( "Hello World", SDL_WINDOWPOS_CENTERED, 
       SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN );
  if( window == NULL ) {
    throw (std::string("Couldn't make a window: ")+SDL_GetError());
  }
  return window;
}

SDL_Renderer* initRenderer(SDL_Window* window) {
  SDL_Renderer* renderer = 
    SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if ( renderer == NULL ) throw std::string("No Renderer");
  return renderer;
}

void draw(const IOmod& io) {
  io.writeText("SDL Sound Player", 200, 50);
  io.writeText("To toggle music: <space>", 50, 110);

  io.writeText("0. Boom", 50, 160);
  io.writeText("1. Gun", 50, 185);
  io.writeText("2. Thump", 50, 210);
  io.writeText("3. Phaser", 50, 235);
  io.writeText("4. Putt Putt", 50, 260);
  io.writeText("5. Explosion", 50, 285);
  io.writeText("6. Cannon   ", 50, 315);
}


int main( ) {
  try {
	  if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		  throw (std::string("Could not init SDL: ") + SDL_GetError());
	  }
	  SDL_Window* window = initWindow();
    SDL_Renderer* renderer = initRenderer(window);

    // Paint the screen teal:
    SDL_SetRenderDrawColor(renderer, 0x05,0xff,0xff, 0xff);
    if ( SDL_RenderClear(renderer) ) {
      throw std::string("oops,coudln't clear screen to Teal!");
    }

    SDLSound sound;
    IOmod& io = IOmod::getInstance();
    io.setRenderer( renderer );

    SDL_Event event;
    const Uint8* keystate;
    bool done = false;
    while ( !done ) {
      while ( SDL_PollEvent(&event) ) {
        keystate = SDL_GetKeyboardState(NULL);
        if (event.type ==  SDL_QUIT) { done = true; break; }
        if(event.type == SDL_KEYDOWN) {
          if (keystate[SDL_SCANCODE_ESCAPE] || keystate[SDL_SCANCODE_Q]) {
            done = true;
            break;
          }
          if ( keystate[SDL_SCANCODE_SPACE] ) {
            sound.toggleMusic();
          }
          if ( keystate[SDL_SCANCODE_0] ) {
            sound[0];
          }
          if ( keystate[SDL_SCANCODE_1] ) {
            sound[1];
          }
          if ( keystate[SDL_SCANCODE_2] ) {
            sound[2];
          }
          if ( keystate[SDL_SCANCODE_3] ) {
            sound[3];
          }
          if ( keystate[SDL_SCANCODE_4] ) {
            sound[4];
          }
          if ( keystate[SDL_SCANCODE_5] ) {
            sound[5];
          }
          if ( keystate[SDL_SCANCODE_6] ) {
            sound[6];
          }
        }
      }

      SDL_RenderClear(renderer);
      draw(io);
      SDL_RenderPresent(renderer);
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow( window );
    SDL_Quit();
  }
  catch( std::string& msg ) {
    std::cerr << msg << std::endl;
  }
  catch ( ... ) {
    std::cout << "oops" << std::endl;
  }
}
