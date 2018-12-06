#include <iostream>
#include <map>
#include <string>
#include <sstream>
using std::cout; using std::endl;
#include "clock.h"
using std::cout; using std::endl;

Clock& Clock::getInstance() {
  if ( SDL_WasInit(SDL_INIT_VIDEO) == 0) {
    throw std::string("Must init SDL before Clock");
  }
  static Clock clock; 
  return clock;
}

Clock::Clock() :
  started(false), 
  paused(false), 
  sloMo(false), 
  frames(0), 
  recentFrames(),
  maxFrames(100),
  tickSum(0),
  timeAtStart(0), timeAtPause(0),
  currTicks(0), prevTicks(0), ticks(0) 
  {
  start();
}

Clock::Clock(const Clock& c) :
  started(c.started), 
  paused(c.paused), 
  sloMo(c.sloMo), 
  frames(c.frames), recentFrames(c.recentFrames), 
  maxFrames(c.maxFrames), tickSum(c.tickSum),
  timeAtStart(c.timeAtStart), timeAtPause(c.timeAtPause),
  currTicks(c.currTicks), prevTicks(c.prevTicks), ticks(c.ticks) 
  {
  start();
}

void Clock::debug( ) { 
  cout << "The clock is:" << endl;
  cout << "\tstarted:" << started << endl;
  cout << "\tpaused:" << paused << endl;
  cout << "\tframes:" << frames << endl;
  cout << "\ttimeAtStart:" << timeAtStart << endl;
  cout << "\ttimeAtPause:" << timeAtPause << endl;
  cout << "\tcurrTicks:" << currTicks << endl;
  cout << "\tprevTicks:" << prevTicks << endl;
  cout << "\tticks:" << ticks << endl;
  cout << endl;
}

void Clock::toggleSloMo() {
  if( started && !sloMo ) {
    timeAtPause = SDL_GetTicks() - timeAtStart;
    sloMo = true;
  }
  else if ( started && sloMo ) {
    timeAtStart = SDL_GetTicks() - timeAtPause;
    sloMo = false;
  }
}

unsigned Clock::getTicks() const { 
  if (paused) return timeAtPause;
  else if ( sloMo ) return 1;
  else return SDL_GetTicks() - timeAtStart; 
}

unsigned Clock::getElapsedTicks() { 
  if (paused) return 0;
  else if ( sloMo ) return 1;
  currTicks = getTicks();
  ticks = currTicks-prevTicks;
  prevTicks = currTicks;
  return ticks;
}

int Clock::getFps() const { 
  if ( getSeconds() > 0 ) return frames/getSeconds();  
  else if ( getTicks() > 1000 and getFrames() == 0 ) {
    throw std::string("Can't getFps if you don't increment the frames");
  }
  else return 0;
}

int Clock::getAvgFps() const { 
  if ( getSeconds() > 0 && recentFrames.size() > maxFrames/2) {
    return recentFrames.size()/(tickSum*0.001);  
  }
  else if ( getTicks() > 1000 and getFrames() == 0 ) {
    throw std::string("Can't getFps if you don't increment the frames");
  }
  else return 0;
}

Clock& Clock::operator++() { 
  if ( !paused ) {
    ++frames; 
    if ( recentFrames.size() >= maxFrames ) { 
      tickSum -= recentFrames.front();
      recentFrames.pop_front(); 
    }
    recentFrames.push_back( ticks );
    tickSum += ticks;
  }
  return *this;
}
Clock  Clock::operator++(int) { 
  if ( !paused ) {
    frames++; 
  }
  return *this;
}

void Clock::start() { 
  started = true; 
  paused = false; 
  frames = 0;
  timeAtPause = timeAtStart = SDL_GetTicks(); 
}
void Clock::pause() {
  if( started && !paused ) {
    timeAtPause = SDL_GetTicks() - timeAtStart;
    paused = true;
  }
}
void Clock::unpause() {
  if( started && paused ) {
    timeAtStart = SDL_GetTicks() - timeAtPause;
    paused = false;
  }
}

