
#include <vector>
#include <SDL.h>
#include <stdlib.h>
#include "math.h"
#include "time.h"
using std::vector;


class ExplodingSprite {
public:
   ExplodingSprite(int x, int y, SDL_Surface* s, SDL_Surface* d)
   {
		mainB = s;
		screen = d;
		dest.x = x;
		dest.y = y;
		dest.w = mainB->w;
		dest.h = mainB->h;
		src.x = 0;
		src.y = 0;
		src.w = dest.w;
		src.h = dest.h;
		maxLevels = 4;
   }
   ExplodingSprite(SDL_Rect sr,SDL_Rect de, char mx, char my, SDL_Surface* s, SDL_Surface* d)
   {
		mainB = s;
		screen = d;
		dest = de;
		src = sr;
		moveX = mx;
		moveY = my;
		X = dest.x;
		Y = dest.y;
		if (src.x < mainB->w/2)
			moveX *=-1;
		if (src.y < mainB->h/2)
			moveY *=-1;;
   }
   void blit() {
      SDL_BlitSurface(mainB, &src, screen, &dest);
   }
   void explodeBlit(vector<ExplodingSprite> & chunks,int i) {
		if (moveX!=0)
			X +=1/(float)moveX;
		if (moveY!=0)
			Y +=1/(float)moveY;
		dest.x = (int)X;
		dest.y = (int)Y;
      SDL_BlitSurface(mainB, &src, screen, &dest);
		if (((X+src.w)<0 || X>screen->w) || ((Y+src.h)<0|| Y>screen->h))
		{
			chunks[i] = chunks[chunks.size()-1];
			chunks.pop_back();
		}
			
   }


void chunkify(vector<ExplodingSprite> & chunks,int x, int y, int w, int h, int level)
{
	bool breakApart;
	breakApart = rand()%2==0?false:true;
	if (level==1)
		breakApart = (rand()%4<3)?true:false;

	if ((breakApart || level<1) && level <4)
	{
		chunkify(chunks,x,y,w/2,h/2,level+1);
		chunkify(chunks,x+w/2,y,w/2,h/2,level+1);
		chunkify(chunks,x,y+h/2,w/2,h/2,level+1);
		chunkify(chunks,x+w/2,y+h/2,w/2,h/2,level+1);
	}
	
	if (level>0 && (!breakApart || level==4))
	{
		SDL_Rect tsrc = {x,y,w,h};
		SDL_Rect tdest = tsrc;
		tdest.x += screen->w/2 - mainB->w/2;
		tdest.y += screen->h/2 - mainB->h/2;
		char tmoveX = (rand()%10);
		char tmoveY = (rand()%10);
		if (tmoveX==0 && moveY==0)
		{
			int tmp = rand()%2;
			if (tmp==1)
				tmoveX = (rand()%9)+1;
			else
				tmoveY = (rand()%9)+1;
		}
		chunks.push_back(ExplodingSprite(tsrc,tdest,tmoveX,tmoveY,mainB,screen));
	}
}
private:
SDL_Rect src,dest;
char moveX,moveY;
float X,Y;
SDL_Surface * mainB, *screen;
int maxLevels;
};
