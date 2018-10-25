#include <string>
#include <vector>
#include <map>
#include "gamedata.h"
#include "sprite.h"
#include "multisprite.h"
#include "multisprite2way.h"

class SpriteFactory {
public:
  static SpriteFactory& getInstance();
  ~SpriteFactory();
  std::map<std::string, Drawable*>::iterator begin();
  std::map<std::string, Drawable*>::iterator end();
  Drawable* addSprite(const std::string&, const int type);
  Drawable* getSprite(const std::string&);
  Drawable* getCurrent();
  Drawable* getNext();
  
  static const int SPRITE;
  static const int MULTI_SPRITE;
  static const int MULTI_SPRITE_2WAY;

private:
  Gamedata*                        gdata;
  std::string                      currentSprite;
  std::map<std::string, Drawable*> sprites;

  SpriteFactory() : 
    gdata( Gamedata::getInstance() ), currentSprite(), sprites()
  {}
  SpriteFactory(const SpriteFactory&);
  SpriteFactory& operator=(const SpriteFactory&);
};
