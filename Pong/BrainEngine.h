//
//  BrainComponent.h
//  Pong
//
//  Created by Giuseppe Acito on 19/04/15.
//  Copyright (c) 2015 CoreDumper. All rights reserved.
//

#ifndef __Pong__BrainComponent__
#define __Pong__BrainComponent__

#include "component.hpp"
#include "AIComponent.hpp"
#include "input_component.hpp"

class BrainEngine {
private:
  static const unsigned int MAX_COMPONENTS = 1;
  AIComponent ai[MAX_COMPONENTS];
  InputComponent components[MAX_COMPONENTS];
  
  unsigned int activeAIComponents;
  unsigned int activeHumanComponents;
  
public:
  BrainEngine() {
    activeAIComponents = 0;
    activeHumanComponents = 0;
  }
  
  ~BrainEngine() {
    this->destroy();
  }
  
  InputComponent* createInputComponent();
  AIComponent* createAIComponent();
  
  void update(double time);
  void destroy();
};

#endif /* defined(__Pong__BrainComponent__) */
