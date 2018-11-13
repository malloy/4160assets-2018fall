#include <vector>
#include <list>
#include "chunk.h"

class ExplodingSprite : public Sprite {
public:
  ExplodingSprite(const Sprite& s);
  ~ExplodingSprite();
  virtual void draw() const;
  virtual void update(Uint32 ticks);
  void makeChunks(unsigned int);
  unsigned int chunkCount() const { return chunks.size(); }
  unsigned int freeCount()  const { return freeList.size(); }
private:
  std::list<Chunk> chunks;
  std::list<Chunk> freeList;
  std::vector<Frame*> frames;
  ExplodingSprite(const ExplodingSprite&);
  ExplodingSprite& operator=(const ExplodingSprite&);
  Vector2f getNewVelocity() const;
};
