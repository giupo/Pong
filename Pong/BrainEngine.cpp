//
//  BrainComponent.cpp
//  Pong
//
//  Created by Giuseppe Acito on 19/04/15.
//  Copyright (c) 2015 CoreDumper. All rights reserved.
//

#include "BrainEngine.h"
#include "AIComponent.hpp"


InputComponent* BrainEngine::createInputComponent() {
  if(activeHumanComponents >= MAX_COMPONENTS) {
    return NULL;
  }
  return &components[activeHumanComponents++];
}

AIComponent* BrainEngine::createAIComponent() {
  if(activeAIComponents >= MAX_COMPONENTS) {
    return NULL;
  }
  return &ai[activeAIComponents++];
}


void BrainEngine::update(double time) {
  for(unsigned int i = 0; i < activeAIComponents; ++i ) {
    ai[i].update(time);
  }
  for(unsigned int i = 0; i < activeHumanComponents; ++i ) {
    components[i].update(time);
  }
}

void BrainEngine::destroy() {
  for(unsigned int i = 0; i < activeAIComponents; ++i ) {
    ai[i].destroy();
  }
  for(unsigned int i = 0; i < activeHumanComponents; ++i ) {
    components[i].destroy();
  }
  
  activeHumanComponents = 0;
  activeAIComponents = 0;
}