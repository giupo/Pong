//
//  ThreadPool.h
//  Pong
//
//  Created by Giuseppe Acito on 05/05/15.
//  Copyright (c) 2015 CoreDumper. All rights reserved.
//

#ifndef __Pong__ThreadPool__
#define __Pong__ThreadPool__

#include <SDL2/SDL.h>
#include <iostream>

class ThreadPool {
private:
  unsigned int cpu_count;
public:
  ThreadPool() {
    Uint32 subsystem_init = SDL_WasInit(SDL_INIT_EVENTS);
    if(subsystem_init != SDL_INIT_EVENTS) {
      std::cout << "SDL was not initializated" << std::endl;
      exit(-1);
    }
    cpu_count = SDL_GetCPUCount();
    
  }
  ~ThreadPool() {}
  
};

#endif /* defined(__Pong__ThreadPool__) */
