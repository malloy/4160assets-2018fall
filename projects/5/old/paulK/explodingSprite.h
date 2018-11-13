#include <vector>
#include <list>
#include "chunk.h"
#include "gamedata.h"

/*
 * Base class for an exploding sprite.
 *
 * The reason for this class is to allow for some functionality without
 * needing to be aware of the template parameters to ExplodingSprite.
 *
 * For example, checking the number of chunks should be the same
 * regardless of how the chunks fly about in the air.
 */
class BaseExplodingSprite : public Sprite {
public:
  BaseExplodingSprite(const Sprite& s);
  virtual ~BaseExplodingSprite();

  unsigned int chunkCount() const { return chunks.size(); }
  unsigned int freeCount()  const { return freeList.size(); }

  virtual void update(Uint32) = 0;
  virtual void makeChunks(unsigned int) = 0;

  virtual void draw() const;

protected:
  std::list<Chunk> chunks; // An ExplodingSprite is a list of sprite chunks
  std::list<Chunk> freeList; // When a chunk gets out of range it goes here
  std::vector<Frame*> frames; // Each chunk has a Frame
private:
  BaseExplodingSprite(const BaseExplodingSprite&);
};


/*
 * Template class for exploding sprite.
 *
 * The template parameters for this class are two functors which are 
 * shown here as 'InitializerT' and 'UpdaterT'. An initializer 
 * encapsulates the method for initializing a chunk, and an updater 
 * defines how the chunks get moved about the scene.
 *
 * More detailed explanation of initializers and updaters is available 
 * in the `functors.h` file along with some example implementations.
 */
template <class InitializerT, class UpdaterT>
class ExplodingSprite : public BaseExplodingSprite {
public:
  ExplodingSprite(const Sprite& s, const InitializerT& f, const UpdaterT& g):
    BaseExplodingSprite(s), 
    initializer(f),
    updater(g)
  {
    makeChunks(Gamedata::getInstance().getXmlInt(s.getName() + "ChunkSize"));
  }

  virtual void update(Uint32 ticks) { 
    std::list<Chunk>::iterator ptr = chunks.begin();
    while (ptr != chunks.end()) {
      ptr->accelerate(ticks, updater(ptr->getPosition()));
      ptr->update(ticks);
      if (ptr->goneTooFar()) {  // Check to see if we should free a chunk
        freeList.push_back(*ptr);
        ptr = chunks.erase(ptr);
      }   
      else ++ptr;
    }
  }

  void makeChunks(unsigned int n) { 
    // Break the SDL_Surface into n*n squares; where each square
    // has width and height of frameWidth/n and frameHeight/n
    const unsigned int
      chunk_width = std::max(1u, getFrame()->getWidth() / n),
      chunk_height = std::max(1u, getFrame()->getHeight() / n);

    // Get the SDL_Surface so we can chunk it:
    SDL_Surface* spriteSurface(getFrame()->getSurface()); 

    // We will update 'source_x' and 'source_y' to reflect the source
    // position from which we will pull the chunk.
    Sint16 source_y = getFrame()->getSourceY();
    while(source_y < getFrame()->getHeight()) {
      Sint16 source_x = getFrame()->getSourceX();
      while(source_x < getFrame()->getWidth()) {
        Frame* frame = 
              new Frame(spriteSurface, chunk_width, chunk_height, source_x, source_y);
        Chunk chunk(
                  Vector2f(X() + source_x,   // x coord of destination 
                           Y() + source_y), // y coord of destination
                  getName()+"Chunk",
                  frame);
        initializer(*this, chunk);
        // chunks uses value semantics, as does frames, but there's
        // a big difference:
        chunks.push_back(chunk);
        frames.push_back(frame);
        source_x += chunk_width;
      }
      source_y += chunk_height;
    }
  }

private:
  const InitializerT initializer;
  const UpdaterT updater;
  ExplodingSprite(const ExplodingSprite&); // Explicit disallow (Item 6)
  ExplodingSprite& operator=(const ExplodingSprite&); // (Item 6)
};
