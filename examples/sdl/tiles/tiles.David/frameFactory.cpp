#include "frameFactory.h"
#include "ioManager.h"
#include "vector2f.h"

FrameFactory::~FrameFactory() 
{
  std::map<std::string, SDL_Surface*>::iterator itSurf = surfaces.begin();
  while ( itSurf != surfaces.end() ) {
    SDL_FreeSurface( itSurf->second );
    ++itSurf;
  }
  std::map<std::string, Frame*>::iterator itFrame = frames.begin();
  while ( itFrame != frames.end() ) {
    delete itFrame->second;
    ++itFrame;
  }
  std::map<std::string, std::vector<Frame*>*>::iterator itMFrame = mframes.begin();
  while ( itMFrame != mframes.end() ) {
    delete itMFrame->second;
    ++itMFrame;
  }
}

FrameFactory& FrameFactory::getInstance() {
  static FrameFactory factory;
  return factory;
}

Frame* FrameFactory::getFrame (const std::string& name) 
{
  std::map<std::string, Frame*>::const_iterator pos = frames.find(name);
  
  
  if ( pos == frames.end() ) 
  {
    SDL_Surface * const surface =
      IOManager::getInstance().loadAndSet(
          gdata->getXmlStr(name+"File"),
          gdata->getXmlBool(name+"Transparency"));
          
    surfaces[name] = surface;
    
    Frame * const frame = new Frame(surface,
                gdata->getXmlInt(name+"Width"), 
                gdata->getXmlInt(name+"Height"),
                gdata->getXmlInt(name+"SrcX"), 
                gdata->getXmlInt(name+"SrcY")); 
    
    frames[name] = frame;
    
    return frame;
  }
  else 
  {
    return pos->second;
  }
}


std::vector<Frame*> FrameFactory::getMFrames (
  const std::string& name, const unsigned int layers) 
{
  std::map<std::string, std::vector<Frame*>*>::const_iterator pos = mframes.find(name);
  if ( pos == mframes.end() ) 
  {
    SDL_Surface * const surface =
      IOManager::getInstance().loadAndSet(
          gdata->getXmlStr (name+"File"),
          gdata->getXmlBool (name+"Transparency"));
          
    surfaces[name] = surface;
    
    
    
    Uint16 numberOfFrames, frameWidth, frameHeight, srcX, srcY;
    
    numberOfFrames = gdata->getXmlInt (name+"Frames"); 
    frameWidth =     gdata->getXmlInt (name+"Width");
    frameHeight =    gdata->getXmlInt (name+"Height");
    srcX =           gdata->getXmlInt (name+"SrcX");
    srcY =           gdata->getXmlInt (name+"SrcY");
    
    std::vector<Frame*>* const framevec = new std::vector<Frame*>;
    framevec->reserve(numberOfFrames*layers);
    
    for (unsigned i=0; i<layers; ++i)
    {
      for (unsigned j = 0; j < numberOfFrames; ++j) 
      {
        unsigned frameY = i * frameHeight + srcY;
        unsigned frameX = j * frameWidth + srcX;
        framevec->push_back ( 
          new Frame(surface, frameWidth, frameHeight, frameX, frameY) );
      }
    }
    
    mframes[name] = framevec;
    
    return *(framevec);
  }
  else 
  {
    return *(pos->second);
  }
}





