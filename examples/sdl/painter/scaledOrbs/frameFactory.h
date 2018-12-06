#include <string>
#include <vector>
#include <map>
#include "frame.h"
#include "gamedata.h"
#include "spriteSheet.h"

class FrameFactory {
public:

  static FrameFactory* getInstance();
  ~FrameFactory();

  Frame* getFrame(const std::string&);
  std::vector<Frame*> getFrames(const std::string&);


private:
  static FrameFactory* instance;
  const Gamedata& gdata;
  std::map<std::string, SDL_Texture*> textures;
  std::map<std::string, Frame*> frames;

  std::map<std::string, std::vector<SDL_Texture*> > multiTextures;
  std::map<std::string, std::vector<Frame*> > multiFrames;

  FrameFactory() : 
    gdata( Gamedata::getInstance() ), 
    textures(),
    frames(),
    multiTextures(),
    multiFrames()
  {}
  FrameFactory(const FrameFactory&);
  FrameFactory& operator=(const FrameFactory&);
};
