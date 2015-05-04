//
//  RenderEngine.cpp
//  Pong
//
//  Created by Giuseppe Acito on 19/04/15.
//  Copyright (c) 2015 CoreDumper. All rights reserved.
//

#include "RenderEngine.h"

RenderEngine::RenderEngine(int width, int height) {
  activeComponents = 0;
  if ( SDL_Init( SDL_INIT_VIDEO  ) < 0 ) {
    printf( "Unable to init SDL: %s\n", SDL_GetError() );
    exit(1);
  }
  // make sure SDL cleans up before exit
  window = SDL_CreateWindow("Pong",
                          SDL_WINDOWPOS_UNDEFINED,
                          SDL_WINDOWPOS_UNDEFINED,
                          width,
                          height,
                          SDL_WINDOW_SHOWN);
  if ( !window ) {
    printf("Unable to set video resolution: %s\n", SDL_GetError());
    exit(1);
  }
  
  renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
  if ( !renderer ) {
    printf("Unable to get screen renderer: %s\n", SDL_GetError());
    exit(1);
  }
  frames = 0;
}

RenderEngine::~RenderEngine() {
  this->destroy();
  SDL_DestroyRenderer( renderer );
  SDL_DestroyWindow( window );
}

RenderComponent* RenderEngine::create() {
  if(activeComponents >= MAX_COMPONENTS) {
    return NULL;
  }
  return &components[activeComponents++];
}

void RenderEngine::update(double time) {
  SDL_RenderClear( renderer );
  SDL_SetRenderDrawColor( renderer, 0, 0, 0, 0xAA );
  
  for(unsigned int i = 0; i < activeComponents; ++i ) {
    components[i].update(time);
  }
  
  SDL_RenderPresent( renderer );
  ++frames;
}

void RenderEngine::destroy() {
  for(unsigned int i = 0; i < activeComponents; ++i ) {
    components[i].destroy();
  }
  activeComponents = 0;
}


void RenderEngine::sync(double delta) {
  if ( delta < SCREEN_TICKS_PER_FRAME ) {
    UInt32 timeToWait = SCREEN_TICKS_PER_FRAME - delta;
    SDL_Delay( timeToWait );
  }
}

