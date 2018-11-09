#include "subjectSprite.h"
#include "smartSprite.h"
#include "gamedata.h"
#include "renderContext.h"

SubjectSprite::SubjectSprite( const std::string& name) :
  MultiSprite(name), 
  observers()
{ }

SubjectSprite::SubjectSprite(const SubjectSprite& s) :
  MultiSprite(s), 
  observers( s.observers )
  { }

void SubjectSprite::detach( SmartSprite* o ) {
  std::list<SmartSprite*>::iterator ptr = observers.begin();
  while ( ptr != observers.end() ) {
    if ( *ptr == o ) {
      ptr = observers.erase(ptr);
      return;
    }
    ++ptr;
  }
}

void SubjectSprite::update(Uint32 ticks) { 
  MultiSprite::update(ticks);
  std::list<SmartSprite*>::iterator ptr = observers.begin();
  while ( ptr != observers.end() ) {
    int offset = rand()%5;
    offset = offset*(rand()%2?-1:1);
    const Vector2f off(offset, offset);
    (*ptr)->setPlayerPos( getPosition()+off );
    ++ptr;
  }
}
