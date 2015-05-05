//
//  component_types.cpp
//  Pong
//
//  Created by Giuseppe Acito on 19/04/15.
//  Copyright (c) 2015 CoreDumper. All rights reserved.
//

#include "component_types.hpp"
#include <string>

const char* NULL_COMPONENT_NAME="nullComponent";
const char* PHYSIC_COMPONENT_NAME="physicComponent";
const char* RENDER_COMPONENT_NAME="renderComponent";
const char* INPUT_COMPONENT_NAME="inputComponent";
const char* AI_COMPONENT_NAME="AIComponent";

ComponentTypes hashComponentName(const char* name) {
  ComponentTypes type = UNKNOWN_COMPONENT;
  
  if(0 == strcmp(name, INPUT_COMPONENT_NAME)) {
    type = INPUT_COMPONENT;
  } else if(0 == strcmp(name, AI_COMPONENT_NAME)) {
    type = AI_COMPONENT;
  } else if(0 == strcmp(name, RENDER_COMPONENT_NAME)) {
    type = RENDER_COMPONENT;
  } else if(0 == strcmp(name, PHYSIC_COMPONENT_NAME)) {
    type = PHYSIC_COMPONENT;
  } else if(0 == strcmp(name, NULL_COMPONENT_NAME)) {
    type = NULL_COMPONENT;
  }
            
  return type;
}