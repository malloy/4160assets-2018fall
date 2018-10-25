#include "spriteFactory.h"
#include "ioManager.h"
#include "vector2f.h"


const int SpriteFactory::SPRITE            = 0;
const int SpriteFactory::MULTI_SPRITE      = 1;
const int SpriteFactory::MULTI_SPRITE_2WAY = 2;


SpriteFactory::~SpriteFactory() 
{
  std::map<std::string, Drawable*>::iterator itSprite = sprites.begin();
  while ( itSprite != sprites.end() ) {
    delete itSprite->second;
    ++itSprite;
  }
}


SpriteFactory& SpriteFactory::getInstance() 
{
  static SpriteFactory factory;
  return factory;
}


std::map<std::string, Drawable*>::iterator SpriteFactory::begin()
{
  return sprites.begin();
}


std::map<std::string, Drawable*>::iterator SpriteFactory::end()
{
  return sprites.end();
}


Drawable* SpriteFactory::addSprite (const std::string& name, const int type) 
{
  std::map<std::string, Drawable*>::const_iterator pos = sprites.find(name);
  
  Drawable* sprite;
  
  if ( pos == sprites.end() ) 
  {
  
    switch (type)
    {
      case SpriteFactory::SPRITE:
        sprite = new Sprite (name);
        sprites[name] = sprite;
        break;
      case SpriteFactory::MULTI_SPRITE:
        sprite = new MultiframeSprite (name);
        sprites[name] = sprite;
        break;
      case SpriteFactory::MULTI_SPRITE_2WAY:
        sprite = new MultiframeSprite2Way (name);
        sprites[name] = sprite;
        break;
      
    }
    
    if (currentSprite.empty()) currentSprite = name;
    
    return sprite;
  }
  else 
  {
    return pos->second;
  }
}


Drawable* SpriteFactory::getSprite (const std::string& name) 
{
  std::map<std::string, Drawable*>::const_iterator pos = sprites.find(name);
  
  if ( pos == sprites.end() ) 
  {
    return ((Drawable*) NULL);
  }
  else 
  {
    return pos->second;
  }
}


Drawable* SpriteFactory::getCurrent ()
{
  return sprites[currentSprite];
} 


Drawable* SpriteFactory::getNext ()
{
  std::map<std::string, Drawable*>::const_iterator it = 
    sprites.find(currentSprite);
  
  ++it;
  if (it==sprites.end()) it = sprites.begin();
  
  currentSprite = it->first;
  
  return it->second;
} 















