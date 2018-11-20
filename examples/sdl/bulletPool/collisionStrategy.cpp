#include <vector>
#include <algorithm>
#include "ioMod.h"
#include "collisionStrategy.h"
#include "viewport.h"
#include "renderContext.h"

void RectangularCollisionStrategy::draw() const {
  IOmod::
  getInstance().writeText("Strategy: Rectangular", 500, 30);
}

bool RectangularCollisionStrategy::execute(
      const Drawable& obj1, const Drawable& obj2) const {
  float left1 = obj1.getX();
  float left2 = obj2.getX();

  float scale1 = obj1.getScale();
  float scale2 = obj2.getScale();

  float right1 = left1+scale1*obj1.getFrame()->getWidth();
  float right2 = left2+scale2*obj2.getFrame()->getWidth();
  if ( right1 < left2 ) return false;
  if ( left1 > right2 ) return false;
  float top1 = obj1.getY();
  float top2 = obj2.getY();
  float bottom1 = top1+scale1*obj1.getFrame()->getHeight();
  float bottom2 = top2+scale2*obj2.getFrame()->getHeight();
  if ( bottom1 < top2 ) return false;
  if ( bottom2 < top1 ) return false;
  return true;
}


float MidPointCollisionStrategy::
distance(float x1, float y1, float x2, float y2) const {
  float x = x1-x2, y = y1-y2;
  return hypot(x, y);
}

void MidPointCollisionStrategy::draw() const {
  IOmod::
  getInstance().writeText("Strategy: Distance", 500, 30);
}

bool MidPointCollisionStrategy::execute(
      const Drawable& obj1, const Drawable& obj2) const {

  float scale1 = obj1.getScale();
  float scale2 = obj2.getScale();

  int width1 = scale1*obj1.getFrame()->getWidth();
  int width2 = scale2*obj2.getFrame()->getWidth();
  int height1 = scale1*obj1.getFrame()->getHeight();
  int height2 = scale2*obj2.getFrame()->getHeight();

  int COLLISION_DISTANCE = width1/2 + width2/2;
  float xobj1 = obj1.getX() + width1/2;
  float yobj1 = obj1.getY() + height1/2;
  float xobj2 = obj2.getX() + width2/2;
  float yobj2 = obj2.getY() + height2/2;
  return distance(xobj1, yobj1, xobj2, yobj2) < COLLISION_DISTANCE;
}


void PerPixelCollisionStrategy::draw() const {
  IOmod::
  getInstance().writeText("Strategy: Per-Pixel ", 500, 30);
}

bool PerPixelCollisionStrategy::
isVisible(Uint32 pixel, SDL_Surface *surface) const {
	Uint32 temp;
	SDL_PixelFormat* fmt = surface->format;
	if(fmt->BitsPerPixel == 32){
		temp=pixel&fmt->Amask; /* Isolate alpha component */
		temp=temp>>fmt->Ashift;/* Shift it down to 8-bit */
		temp=temp<<fmt->Aloss; /* Expand to a full 8-bit number */
		if(temp == 0) return false;
	}
	return true;
}

// This is, essentially, SpriteSheet::cropSurface:
SDL_Surface* scaleSurface(SDL_Surface* surf, int width, int height) {

  const auto* fmt = surf->format;
  SDL_Surface* sub = SDL_CreateRGBSurface(0,width,height,
                     fmt->BitsPerPixel,fmt->Rmask,fmt->Gmask,
                     fmt->Bmask,fmt->Amask);

  // Get the old mode
  SDL_BlendMode oldBlendMode;
  SDL_GetSurfaceBlendMode(surf, &oldBlendMode);

  // Set the new mode so copying the source won't change the source
  SDL_SetSurfaceBlendMode(surf, SDL_BLENDMODE_NONE);

  SDL_Rect rect = {0,0,width,height};
  int flag = SDL_BlitScaled(surf,nullptr,sub,&rect);
  if ( flag < 0 ) throw( std::string("SDL_BlitScaled failed!") );
  //std::cout << width  << ", " << surf->w << ", " << sub->w << std::endl;

  // Set the blend mode back to original
  SDL_SetSurfaceBlendMode(surf, oldBlendMode);
  return sub;
}

bool PerPixelCollisionStrategy::execute(
      const Drawable& obj1, const Drawable& obj2) const {

  RectangularCollisionStrategy strategy;
  if ( not strategy.execute(obj1, obj2) ) return false;
  // If we got this far, we know that the sprite rectangles intersect!

  Vector2f p1 = obj1.getPosition() - Viewport::getInstance().getPosition();
  Vector2f p2 = obj2.getPosition() - Viewport::getInstance().getPosition();

  float scale1 = obj1.getScale();
  const Frame * const frame1 = obj1.getFrame();
  Uint16 width1 = scale1*frame1->getWidth();
  Uint16 height1 = scale1*frame1->getHeight();

  float scale2 = obj2.getScale();
  const Frame * const frame2 = obj2.getFrame();
  Uint16 width2 = scale2*frame2->getWidth();
  Uint16 height2 = scale2*frame2->getHeight();

  int o1Left = p1[0]; 
  int o1Right = o1Left+width1;

  int o2Left = p2[0]; 
  int o2Right = o2Left+width2;
  std::vector<int> sides;
  sides.reserve(4);
  sides.push_back( o1Left );
  sides.push_back( o1Right );
  sides.push_back( o2Left );
  sides.push_back( o2Right );
  std::sort( sides.begin(), sides.end() );


  int o1Up = p1[1];
  int o1Down = o1Up+height1;
  int o2Up = p2[1];
  int o2Down = o2Up+height2;
  std::vector<int> lids;
  lids.reserve(4);
  lids.push_back( o1Up );
  lids.push_back( o1Down );
  lids.push_back( o2Up );
  lids.push_back( o2Down );
  std::sort( lids.begin(), lids.end() );

  SDL_Surface* temp1 = 
    RenderContext::getInstance()->getSurface(obj1.getName());
  SDL_Surface* surface1 = scaleSurface(temp1, width1, height1);
  SDL_Surface* temp2 = 
    RenderContext::getInstance()->getSurface(obj2.getName());
  SDL_Surface* surface2 = scaleSurface(temp2, width2, height2);

  SDL_LockSurface(surface1);
  SDL_LockSurface(surface2);
  Uint32 *pixels1 = static_cast<Uint32 *>(surface1->pixels);
  Uint32 *pixels2 = static_cast<Uint32 *>(surface2->pixels);
  unsigned pixel1;
  unsigned pixel2;
  for (int x = sides[1]; x < sides[2]; ++x) {
    for (int y = lids[1]; y < lids[2]; ++y) {
      // check pixels in surface for obj1 and surface for obj2!
      int i = x - p1[0];
      int j = y - p1[1];
      pixel1 = pixels1[ (j * width1) + i ];
      i = x - p2[0];
      j = y - p2[1];
      pixel2 = pixels2[ (j * width2) + i ];

      if ( isVisible(pixel1,surface1) && isVisible(pixel2,surface2) ) {
        SDL_UnlockSurface(surface1);
        SDL_UnlockSurface(surface2);
        SDL_FreeSurface(surface1);
        SDL_FreeSurface(surface2);
        return true;
      }
    }
  }
  SDL_UnlockSurface(surface1);
  SDL_UnlockSurface(surface2);
  SDL_FreeSurface(surface1);
  SDL_FreeSurface(surface2);

  return false;
}

