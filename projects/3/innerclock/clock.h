#include <SDL.h>
#include <string>
#include "engine.h"

class Engine;

class Engine::Clock {
public:
  static Clock& getInstance();
  unsigned int getTicks() const;
  unsigned int getElapsedTicks();
  bool isPaused() const  { return paused;  }

  void pause();
  void unpause();
  void incrFrame();

private:
  bool started;
  bool paused;

  const bool FRAME_CAP_ON;
  const Uint32 PERIOD;

  unsigned int frames;

  unsigned int timeAtStart;
  unsigned int timeAtPause;
  unsigned int currTicks;
  unsigned int prevTicks;
  unsigned int ticks;

  void toggleSloMo();

  bool isStarted() const { return started; }
  unsigned int getFrames() const  { return frames;  }
  unsigned int getSeconds() const { return getTicks()/1000;  }
  unsigned int capFrameRate() const;
  int getFps() const;

  void startClock();

  Clock();
  Clock(const Clock&);
  Clock&operator=(const Clock&);
};
