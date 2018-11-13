#ifdef WIN32
#pragma comment(lib, "SDL.lib")
#pragma comment(lib, "SDLmain.lib")
#endif

#include "explodedSprite.h"

SDL_Surface * mainB, *screen;

int main(int , char ** )
{
	   srand( (unsigned)time( NULL ) );
	   vector<ExplodingSprite> chunks;

	   SDL_Event event;
      SDL_Init(SDL_INIT_VIDEO);
      // Attempt to set a 640x480 hicolor (16-bit) video mode.
      screen = SDL_SetVideoMode(640, 480, 16, SDL_DOUBLEBUF);
	  mainB = SDL_LoadBMP("images/spaceship.bmp");
      SDL_SetColorKey(mainB, SDL_SRCCOLORKEY,
          Uint16(SDL_MapRGB(mainB->format, 0, 0, 0)));
	  ExplodingSprite sprite(screen->w/2-mainB->w/2, screen->h/2-mainB->h/2, mainB, screen);
	  sprite.chunkify(chunks,0,0,mainB->w,mainB->h,0);
	  bool explode = false;
	  while(true)
	  {
		  SDL_FillRect(screen, NULL, 0);
		  if (SDL_PollEvent(&event))
		  {
			  if (event.type == SDL_QUIT) break;
			  else if (event.type == SDL_KEYDOWN)
			  {
				  if (event.key.keysym.sym == SDLK_ESCAPE) break;
				  if (event.key.keysym.sym == SDLK_e)
				  {
					  if (explode)
					  {
						chunks.clear();
						sprite.chunkify(chunks,0,0,mainB->w,mainB->h,0);
					  }
					  explode = !explode;
				  }
			  }
		  }
		if (!explode)
			sprite.blit();
		else
			for (unsigned int i=0;i<chunks.size();i++)
				chunks[i].explodeBlit(chunks,i);
		SDL_Flip(screen);
	  }
	  return 0;
}

