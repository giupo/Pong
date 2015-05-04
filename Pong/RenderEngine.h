//
//  RenderEngine.h
//  Pong
//
//  Created by Giuseppe Acito on 19/04/15.
//  Copyright (c) 2015 CoreDumper. All rights reserved.
//

#ifndef __Pong__RenderEngine__
#define __Pong__RenderEngine__

#include "chipmunk.h"
#include "tinyxml2.h"
#include "physic_comp.hpp"
#include <SDL2/SDL.h>

using namespace tinyxml2;

class RenderEngine {
private:
  const int SCREEN_FPS = 60;
  const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;
  
  const unsigned short SCREEN_DEPTH = 32;
  
  static const unsigned int MAX_COMPONENTS = 10;
  RenderComponent components[MAX_COMPONENTS];
  unsigned int activeComponents;
  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_Surface* screen;
  unsigned long long frames;
public:
  RenderEngine(int width, int height);
  
  ~RenderEngine();
 
  RenderComponent* create();
  
  SDL_Renderer* getRenderer() {
    return renderer;
  }
  
  unsigned long long getFrames() {
    return frames;
  }
  
  void sync(double delta);
  
  void update(double time);
  void destroy();
};

#endif /* defined(__Pong__RenderEngine__) */
