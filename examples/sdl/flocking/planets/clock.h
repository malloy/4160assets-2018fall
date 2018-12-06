#include <SDL.h>
#include <string>
#include <iostream>
#include <fstream>
#include <deque>

class Manager;

class Clock {
public:
  static Clock& getInstance();
  unsigned getTicks() const;

private:
  friend class Manager;
  unsigned getElapsedTicks();
  Clock& operator++();
  Clock  operator++(int);
  void toggleSloMo();

  bool isStarted() const { return started; }
  bool isPaused() const  { return paused;  }
  unsigned getFrames() const  { return frames;  }
  unsigned getSeconds() const { return getTicks()/1000;  }
  int getFps() const;
  int getAvgFps() const;

  void start();
  void pause();
  void unpause();
  void debug();
  //void save(std::fstream& xmlfile) const;
  //void restore(const std::string& filename);

  bool started;
  bool paused;
  bool sloMo;

  unsigned frames;
  std::deque<int> recentFrames;
  unsigned maxFrames;
  unsigned tickSum;
  unsigned timeAtStart;
  unsigned timeAtPause;
  unsigned currTicks;
  unsigned prevTicks;
  unsigned ticks;

  Clock();
  Clock(const Clock&);
  Clock&operator=(const Clock&);
};
