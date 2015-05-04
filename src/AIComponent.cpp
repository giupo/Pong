//
//  AIComponent.cpp
//  Pong
//
//  Created by Giuseppe Acito on 19/04/15.
//  Copyright (c) 2015 CoreDumper. All rights reserved.
//

#include "AIComponent.hpp"

void AIComponent::init(XMLNode *node){
  id = (ComponentId) atoi(node->ToElement()->Attribute("id"));
}

void AIComponent::destroy() {
  
}
void AIComponent::update(double time) {
  if(is_paused) {
    
  } else {
    
  }
}

void AIComponent::onNotify(Message& message) {
  int type = message.type;
  switch (type) {
    case BALL_COMING:
      is_paused = false;
      break;
    case BALL_POSITION: {
      Vect* position = (Vect*) message.payload;
      ball_position.x = position->x;
      ball_position.y = position->y;
      break;
    }
    default:
      break;
  }
}
