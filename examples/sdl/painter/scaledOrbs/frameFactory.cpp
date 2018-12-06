#include "ioMod.h"
#include "vector2f.h"
#include "renderContext.h"

FrameFactory* FrameFactory::getInstance() {
  if ( !instance ) instance = new FrameFactory;
  return instance;
}

FrameFactory::~FrameFactory() {
  std::cout << "Deleting frames in Factory" << std::endl;
  // Free single frame containers
  for(auto& ti : textures) SDL_DestroyTexture(ti.second);
  for(auto& fi : frames  ) delete fi.second;

  // Free multi-frame containers
  std::map<std::string, std::vector<SDL_Texture*> >::iterator 
    textures = multiTextures.begin();
  while ( textures != multiTextures.end() ) {
    for (unsigned int i = 0; i < textures->second.size(); ++i) {
      SDL_DestroyTexture( textures->second[i] );
    }
    ++textures;
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

Frame* FrameFactory::getFrame(const std::string& name) {
    std::map<std::string, Frame*>::const_iterator it = frames.find(name); 
  if ( it == frames.end() ) {
    SDL_Texture * const texture =
      IOmod::getInstance().readTexture( gdata.getXmlStr(name+"/file"));
    textures[name] = texture;
    Frame * const frame =new Frame(texture);
    frames[name] = frame;
    return frame;
  }
  else {
    return it->second;
  }
}


std::vector<Frame*> FrameFactory::getFrames(const std::string& name) {
  // First search map to see if we've already made it:
  std::map<std::string, std::vector<Frame*> >::const_iterator 
    pos = multiFrames.find(name); 
  if ( pos != multiFrames.end() ) {
    return pos->second;
  }

  IOmod& iomod = IOmod::getInstance();
  RenderContext* gctx  = RenderContext::getInstance();
  std::string sheetPath = gdata.getXmlStr(name+"/file");
  SDL_Surface* surface = iomod.readSurface(sheetPath);

  // It wasn't in the map, so we have to make the vector of Frames:
  unsigned numberOfFrames = gdata.getXmlInt(name+"/frames");
  std::vector<Frame*> frames;
  std::vector<SDL_Texture*> textures;
  frames.reserve(numberOfFrames);
  textures.reserve(numberOfFrames);

  int width = surface->w/numberOfFrames;
  int height = surface->h;

  if(  gdata.checkTag(name+"/frameWidth") 
    && gdata.checkTag(name+"/frameHeight") ){
    width  = gdata.getXmlInt(name+"/frameWidth");
    height = gdata.getXmlInt(name+"/frameHeight");
  }

  SpriteSheet sheet(surface,width,height);

  SDL_Texture* tex;
  for (unsigned i = 0; i < numberOfFrames; ++i) {
    SDL_Surface* sub = sheet[i];
    tex = SDL_CreateTextureFromSurface(gctx->getRenderer(),sub);
    textures.push_back( tex );
    frames.push_back( new Frame(tex) );
    SDL_FreeSurface(sub);
  }
  multiTextures[name] = textures;
  multiFrames[name] = frames;
  return frames;
}

