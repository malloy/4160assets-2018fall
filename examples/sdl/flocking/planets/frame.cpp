#include "SDL/SDL_rotozoom.h"
#include "drawable.h"
#include "frame.h"
#include "ioManager.h"
#include "viewport.h"

Frame::Frame( const std::string& name, SDL_Surface* surf ) : 
  screen(IOManager::getInstance().getScreen()),
  surface( surf ),
  width(Gamedata::getInstance().getXmlInt(name+"Width")), 
  height(Gamedata::getInstance().getXmlInt(name+"Height")),
  sourceX(0),
  sourceY(0)
{ }

Frame::Frame( SDL_Surface* spr, Uint16 w, Uint16 h,
              Sint16 src_x, Sint16 src_y) :
  screen(IOManager::getInstance().getScreen()),
  surface(spr), 
  width(w), height(h),
  sourceX(src_x), sourceY(src_y) {
}

Frame& Frame::operator=(const Frame& rhs) {
  surface = rhs.surface;
  screen = rhs.screen;
  width = rhs.width;
  height = rhs.height;
  sourceX = rhs.sourceX;
  sourceY = rhs.sourceY;
  return *this;
}

void Frame::draw(Sint16 x, Sint16 y) const {
  SDL_Rect src = { sourceX, sourceY, width, height };    
  x -= Viewport::getInstance().X();
  y -= Viewport::getInstance().Y();
  SDL_Rect dest = {x, y, width, height };
  SDL_BlitSurface(surface, &src, screen, &dest);
}

void Frame::draw(Sint16 sx, Sint16 sy, Sint16 dx, Sint16 dy) const {
  SDL_Rect src = { sx, sy, width, height };    
  SDL_Rect dest = {dx, dy, width, height };
  SDL_BlitSurface(surface, &src, screen, &dest);
}

void Frame::draw(Sint16 x, Sint16 y, double angle) const {
  SDL_Surface* tmp = rotozoomSurface(surface, angle, 1, 1);
  SDL_Rect src = { 0, 0, tmp->w, tmp->h };    
  x -= Viewport::getInstance().X();
  y -= Viewport::getInstance().Y();
  SDL_Rect dest = {x, y, 0, 0 };
  SDL_BlitSurface(tmp, &src, screen, &dest);
  SDL_FreeSurface( tmp );
}

void Frame::draw(Sint16 x, Sint16 y, double angle, 
                 float flipx, float flipy) const {
  SDL_Surface* tmp = rotozoomSurfaceXY(surface, angle, flipx, flipy, 0);
  SDL_Rect src = { 0, 0, tmp->w, tmp->h };
  x -= Viewport::getInstance().X();
  y -= Viewport::getInstance().Y();
  SDL_Rect dest = {x, y, 0, 0 };
  SDL_BlitSurface(tmp, &src, screen, &dest);
  SDL_FreeSurface( tmp );
}
