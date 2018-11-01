#include <iostream>
#include <iomanip>
#include "ioManager.h"
using std::string;
const int FONT_SIZE = 14;

IOManager* IOManager::getInstance() {
  if (!instance) instance = new IOManager(); 
  return instance;
}

IOManager::IOManager( ) 
    // The 3rd and 4th parameters are just as important as the first 2!
  : screen(SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_HWSURFACE)),
    font( NULL ), inputString("")  {
  if (screen == NULL) { 
    throw string("Unable to set video mode"); 
  }
  if ( TTF_Init() == -1 ) {
    throw string("TTF_Init failed: ") + TTF_GetError();
  }
  font = TTF_OpenFont("font/pirulen.ttf", FONT_SIZE);
  if ( !font ) {
    throw string("TTF_OpenFont failed: ") + TTF_GetError();
  }
  SDL_EnableUNICODE( SDL_ENABLE );
  atexit(TTF_Quit);
}

SDL_Surface* IOManager::loadAndSet(const char* filename, bool setcolorkey) const {
  SDL_Surface *tmp = IMG_Load(filename);
  if (tmp == NULL) {
    throw string("Unable to load bitmap ")+filename;
  }
  if ( setcolorkey ) {
    Uint32 colorkey = SDL_MapRGB(tmp->format, 255, 0, 255);
    SDL_SetColorKey(tmp, SDL_SRCCOLORKEY|SDL_RLEACCEL, colorkey);
  }
  // Optimize the strip for fast display
  SDL_Surface *image = SDL_DisplayFormat(tmp);
  if (image == NULL) {
    image = tmp;
  } 
  else {
    SDL_FreeSurface(tmp);
  }
  return image;
}

void IOManager::printMessageAt(const string& msg, Uint32 x, Uint32 y) const {
   SDL_Rect dest = {x,y,0,0};
   SDL_Color color = {0, 0, 0, 0};
   SDL_Surface * stext = TTF_RenderText_Blended(font, msg.c_str(), color);
   if (stext) {
     SDL_BlitSurface( stext, NULL, screen, &dest );
     SDL_FreeSurface(stext);
   }
   else {
     throw 
     string("Couldn't allocate text sureface in printMessageAt");
   }
}

void IOManager::printMessageCenteredAt( const string& msg, Uint32 y) const {
   SDL_Color color = {0, 0, 0, 0};
   SDL_Surface *stext = TTF_RenderText_Blended(font, msg.c_str(), color);
   if (stext) {
     Uint32 x = ( WIDTH - stext->w ) / 2;
     SDL_Rect dest = {x,y,0,0};
     SDL_BlitSurface( stext, NULL, screen, &dest );
     SDL_FreeSurface(stext);
   }
   else {
     throw 
     string("Couldn't allocate text sureface in printMessageCenteredAt");
   }
}

void IOManager::printMessageValueAt(const string& msg, float value, 
     Uint32 x, Uint32 y) const {
   std::stringstream strm;
   std::string message = msg;
   strm.setf(std::ios::fixed, std::ios::floatfield);
   strm.setf(std::ios::showpoint);
   strm << message << std::setprecision(2);
   strm << value << "\0";
   message = strm.str();
   SDL_Rect dest = {x,y,0,0};
   SDL_Color color = {0, 0, 0, 0};
   SDL_Surface *stext = TTF_RenderText_Blended(font, message.c_str(), color);
   if (stext) {
     SDL_BlitSurface( stext, NULL, screen, &dest );
     SDL_FreeSurface(stext);
   }
   else {
     throw 
     string("Couldn't allocate text sureface in printMessageValueAt");
   }
}

void IOManager::printStringAfterMessage( const string& msg,
       Uint32 x, Uint32 y ) const {
   printMessageAt(msg+inputString, x, y);
}

void IOManager::buildString(SDL_Event event) {
  if( inputString.size() <= MAX_STRING ) {
    unsigned ch = event.key.keysym.sym;
    if ( isalpha(ch) || isdigit(ch) || ch == ' ') {
      inputString += char(event.key.keysym.unicode);
    }
  }     
  if( event.key.keysym.sym == SDLK_BACKSPACE
      && inputString.length() > 0 ) {
      // remove a character from the end
      int length = inputString.size();
      inputString.erase( length - 1 );
  }
}

