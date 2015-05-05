//
//  AIComponent.cpp
//  Pong
//
//  Created by Giuseppe Acito on 19/04/15.
//  Copyright (c) 2015 CoreDumper. All rights reserved.
//

#include "AIComponent.hpp"
#include "util_functions.h"
#include <iostream>
#include <cmath> 

void AIComponent::init(XMLNode *node){
  id = (ComponentId) atoi(node->ToElement()->Attribute("id"));
}

void AIComponent::destroy() {
  
}

void AIComponent::update(double time) {
  cpVect impulse = { 0, 0 };
  cpFloat product = cpvdot(*normal, *other_velocity);
  const double thr = 0.0001;
  if(product > -thr) {
    cpFloat diff = position->y - other_position->y;
    impulse.y = diff/3.2;
  } else if(product < thr) {
    cpFloat diff = getScreenHeight() - position->y;
    diff = diff/std::abs(diff)/2;
    impulse.y = diff;
  } else {
    // non fare niente;
    return;
  }
  if (cpvlength(impulse) < thr) {
    // impulso e' nullo, ritorno senza fare niente;
    return;
  }
  std::cout << "Apply impulse " << impulse.x << ", " << impulse.y << std::endl;
  std::cout << "product : " << product << std::endl;
  std::cout << normal->x << "," << normal->y << std::endl;
  std::cout << other_velocity->x << ", "<< other_velocity->y << std::endl;
  Message msg;
  msg.type = PLAYER_IMPULSE;
  msg.payload = &impulse;
  for(const auto& comp: *observers) {
    comp->onNotify(msg);
  }
}

void AIComponent::onNotify(Message& message) {
  switch (message.type) {
    case OTHER_POSITION: {
      cpVect v = (cpVect&) *message.payload;
      other_position->x = v.x;
      other_position->y = v.y;
      break;
    }
      
    case OTHER_VELOCITY: {
      cpVect v = (cpVect&) *message.payload;
      other_velocity->x = v.x;
      other_velocity->y = v.y;
      break;
    }
      
    case PLAYER_POSITION: {
      cpVect v = (cpVect&) *message.payload;
      position->x = v.x;
      position->y = v.y;
      break;
    }
      
    case PLAYER_VELOCITY: {
      cpVect v = (cpVect&) *message.payload;
      velocity->x = v.x;
      velocity->y = v.y;
      break;
    }
    
    case NORMAL_VECTOR: {
      cpVect v = (cpVect&) *message.payload;
      if(v.x == 0 && v.y == 0) {
        return;
      }
      normal->x = v.x;
      normal->y = v.y;
      break;
    }
      
    default:
      break;
  }
}
