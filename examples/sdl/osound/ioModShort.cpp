#include <SDL_image.h>
#include "ioModShort.h"

IOmod& IOmod::getInstance() {
  static IOmod instance;
  return instance;
}

IOmod::~IOmod() { 
  TTF_CloseFont(font);
  TTF_Quit(); 
}

IOmod::IOmod() : 
  init(TTF_Init()),
  font(TTF_OpenFont("fonts/arial.ttf", 24)),
  textColor({0xff, 0, 0, 0}),
  renderer(nullptr)
{
  if ( init == -1 ) {
    throw std::string("error: Couldn't init font");
  }
  if (font == NULL) {
    throw std::string("error: font not found");
  }
  textColor.r = 255;
  textColor.g = 0;
  textColor.b = 0;
  textColor.a = 255;
}

void IOmod::writeText(const std::string& msg, int x, int y) const {
  int textWidth;
  int textHeight;

  SDL_Surface* surface = 
    TTF_RenderText_Solid(font, msg.c_str(), textColor);

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

  textWidth = surface->w;
  textHeight = surface->h;
  SDL_FreeSurface(surface);
  SDL_Rect dst = {x, y, textWidth, textHeight};

  SDL_RenderCopy(renderer, texture, NULL, &dst);
  SDL_DestroyTexture(texture);
}
