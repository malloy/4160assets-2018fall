#include <sys/stat.h>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include "frameGenerator.h"

FrameGenerator::
FrameGenerator(SDL_Renderer* rend, SDL_Window*  win, int w, int h, 
               const std::string& n) :
  renderer(rend), 
  window(win), 
  WIDTH( w ),
  HEIGHT( h ),
  USERNAME( n )
{
  struct stat info;
  if( stat( "frames", &info ) != 0 ) {
    mkdir("frames", 0755);
  }
}


void FrameGenerator::makeFrame() {
  // Pixel format is argb
  SDL_Surface* screenCap = SDL_GetWindowSurface(window);
  if ( screenCap ) {
    SDL_RenderReadPixels(renderer, NULL, 
      SDL_GetWindowPixelFormat(window), 
      screenCap->pixels, screenCap->pitch); 
  }
  else {
    std::cout << SDL_GetError() << std::endl;
    throw std::string("Couldn't make screenCap in makeFrame");
  }
  std::stringstream strm;
  strm << "frames/" << USERNAME << ".bmp"; 
  std::string filename( strm.str() );
  std::cout << "Making frame: " << filename << std::endl;
  SDL_SaveBMP(screenCap, filename.c_str());
  SDL_FreeSurface(screenCap);
}

