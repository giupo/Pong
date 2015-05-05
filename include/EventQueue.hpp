//
//  EventQueue.h
//  Pong
//
//  Created by Giuseppe Acito on 05/05/15.
//  Copyright (c) 2015 CoreDumper. All rights reserved.
//

#ifndef __Pong__EventQueue__
#define __Pong__EventQueue__

#include <iostream>
#include <SDL2/SDL.h>
#include <vector>

#include "component_messages.hpp"
#include "locator.hpp"
#include "game.hpp"

class EventQueue {
  SDL_mutex* mutex;
  unsigned int head;
  unsigned int tail;
  static const int MAX_PENDING = 100;
  Message queue[MAX_PENDING];
public:
  EventQueue() {
    Uint32 subsystem_init = SDL_WasInit(SDL_INIT_EVENTS);
    if(subsystem_init != SDL_INIT_EVENTS) {
      std::cout << "SDL Event was not initializated" << std::endl;
      exit(-1);
    }
    
    mutex = SDL_CreateMutex();
    if (!mutex) {
      std::cerr <<  "Couldn't create mutex" << std::endl;
      return;
    }
    head = 0;
    tail = 0;
  }
  
  void enqueue(Message* msg) {
    
    
    if (SDL_LockMutex(mutex) != 0) {
      return;
    }
    
    assert((tail + 1) % MAX_PENDING != head);
    queue[tail].id = msg->id;
    queue[tail].payload = msg->payload;
    queue[tail].type = msg->type;
    tail = (tail + 1) % MAX_PENDING;
    SDL_UnlockMutex(mutex);
  }
  
  Message* pop() {
    if (head == tail) return NULL;
    
    if (SDL_LockMutex(mutex) != 0) {
      return NULL;
    }
    Message* message = &queue[head];
    head = (head + 1) % MAX_PENDING;
    SDL_UnlockMutex(mutex);
    return message;
  }
  
  Message* peek() {
    if (SDL_LockMutex(mutex) != 0) {
      return NULL;
    }
    Message* message = &queue[head];
    SDL_UnlockMutex(mutex);
    return message;
  }
  
  void poll_events() {
    SDL_Event event;
    Game* game = Locator::getGame();
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_USEREVENT: {
          
          if( event.user.code == 1 ) {
            cout << "vince 1"<<endl;
            game->incrementScore1();
            game->resetActors();
            game->kick();
            continue;
          } else if ( event.user.code == 2 ) {
            game->incrementScore2();
            game->resetActors();
            game->kick();
            continue;
          }

          break;
        }
        case SDL_APP_TERMINATING: {
          game->destroy();
          break;
        }
          
        case SDL_APP_LOWMEMORY: {
          Locator::getResourceManager()->purge();
          break;
        }
        case SDL_APP_WILLENTERBACKGROUND: {
          game->destroy();
          break;
        }
        case SDL_APP_DIDENTERBACKGROUND: {
          break;
        }
        
        case SDL_APP_WILLENTERFOREGROUND: {
          game->init();
          game->loop();
          break;
        }
        case SDL_APP_DIDENTERFOREGROUND:
          break;
        case SDL_QUIT: {
          game->destroy();
          break;
        }
      } // end switch
    }

  }
  
  ~EventQueue() {
    SDL_DestroyMutex(mutex);
  }
};
#endif /* defined(__Pong__EventQueue__) */
