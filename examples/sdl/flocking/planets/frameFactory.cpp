#include "frameFactory.h"
#include "extractSurface.h"
#include "ioManager.h"
#include "vector2f.h"

FrameFactory::~FrameFactory() {
  std::cout << "Deleting FrameFactory" << std::endl;
  std::map<std::string, SDL_Surface*>::iterator itSurf = surfaces.begin();
  while ( itSurf != surfaces.end() ) {
    SDL_FreeSurface( itSurf->second );
    ++itSurf;
  }
  std::map<std::string, std::vector<SDL_Surface*> >::iterator 
    surfaces = multiSurfaces.begin();
  while ( surfaces != multiSurfaces.end() ) {
    for (unsigned int i = 0; i < surfaces->second.size(); ++i) {
      SDL_FreeSurface( surfaces->second[i] );
    }
    ++surfaces;
  }
  std::map<std::string, Frame*>::iterator frame = frames.begin();
  while ( frame != frames.end() ) {
    delete frame->second;
    ++frame;
  }
  std::map<std::string, std::vector<Frame*> >::iterator 
    frames = multiFrames.begin();
  while ( frames != multiFrames.end() ) {
    for (unsigned int i = 0; i < frames->second.size(); ++i) {
      delete frames->second[i];
    }
    ++frames;
  }
}

FrameFactory& FrameFactory::getInstance() {
  static FrameFactory factory;
  return factory;
}

Frame* FrameFactory::getFrame(const std::string& name) {
    std::map<std::string, Frame*>::const_iterator pos = frames.find(name); 
  if ( pos == frames.end() ) {
    SDL_Surface * const surface =
      IOManager::getInstance().loadAndSet(
          gdata.getXmlStr(name+"File"),
          gdata.getXmlBool(name+"Transparency"));
    surfaces[name] = surface;
    Frame * const frame =new Frame(name, surface);
    frames[name] = frame;
    return frame;
  }
  else {
    return pos->second;
  }
}

std::vector<Frame*> FrameFactory::getFrames(const std::string& name) {
  // First search map to see if we've already made it:
  std::map<std::string, std::vector<Frame*> >::const_iterator 
    pos = multiFrames.find(name); 
  if ( pos != multiFrames.end() ) {
    return pos->second;
  }

  // It wasn't in the map, so we have to make the vector of Frames:
  SDL_Surface* surface = IOManager::
     getInstance().loadAndSet(gdata.getXmlStr(name+"File"), true);
  unsigned numberOfFrames = gdata.getXmlInt(name+"Frames");
  std::vector<Frame*> frames;
  std::vector<SDL_Surface*> surfaces;
  frames.reserve(numberOfFrames);
  Uint16 srcX = gdata.getXmlInt(name+"SrcX");
  Uint16 srcY = gdata.getXmlInt(name+"SrcY");
  Uint16 width = gdata.getXmlInt(name+"Width");
  Uint16 height = gdata.getXmlInt(name+"Height");

  SDL_Surface* surf;
  for (unsigned i = 0; i < numberOfFrames; ++i) {
    unsigned frameX = i * width + srcX;
   surf = ExtractSurface::getInstance().
               get(surface, width, height, frameX, srcY); 
    surfaces.push_back( surf );
    frames.push_back( new Frame(name, surf) );
  }
  SDL_FreeSurface(surface);
  multiSurfaces[name] = surfaces;
  multiFrames[name] = frames;
  return frames;
}
