//
//  AIComponent.cpp
//  Pong
//
//  Created by Giuseppe Acito on 19/04/15.
//  Copyright (c) 2015 CoreDumper. All rights reserved.
//

#include "AIComponent.hpp"
#include "BallPhysicComponent.hpp"

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
    case BALL_POSITION: {
      BallPhysicComponent* pc = (BallPhysicComponent*) message.payload;
      ball_position.x = pc->getPosition().x;
      ball_position.y = pc->getPosition().y;
      break;
    }
    default:
      break;
  }
}
