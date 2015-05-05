

#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <vector>
#include <map>

#include <SDL2/SDL.h>
#include "timer.hpp"
#include "util_functions.h"
#include "actor.hpp"
#include "RenderEngine.h"
#include "BrainEngine.h"

#include "locator.hpp"

inline bool checkCollision(SDL_Rect a, SDL_Rect b);



class Game {
  Timer timer;
  long long frames;
  bool running;
  const static unsigned int MAX_ACTORS = 3;
  Actor actors[MAX_ACTORS];
  int activeActors;
  unsigned int score1;
  unsigned int score2;
public:
  static unsigned short width;
  static unsigned short height;

  Game(int width, int height);

  Game() {
    Game(getScreenWidth(), getScreenHeight());
  }

  ~Game();
  void loop();
  void destroy();
  void init();
  void reset();
  void kick();
  void resetActors() {
    for(int i=0; i < activeActors; i++) {
      actors[i].reset();
    }
  }
};

#endif
