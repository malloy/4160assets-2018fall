#include <string>
#include <vector>
#include <map>
#include "frame.h"
#include "gamedata.h"

class FrameFactory {
public:
  static FrameFactory& getInstance();
  ~FrameFactory();
  Frame* getFrame(const std::string&);
  std::vector<Frame*> getMFrames(const std::string&, const unsigned int layers);

private:
  Gamedata* gdata;
  std::map<std::string, SDL_Surface*> surfaces;
  std::map<std::string, Frame*> frames;
  std::map<std::string, std::vector<Frame*>* > mframes;

  FrameFactory() : 
    gdata( Gamedata::getInstance() ), surfaces(), frames(), mframes()
  {}
  FrameFactory(const FrameFactory&);
  FrameFactory& operator=(const FrameFactory&);
};
