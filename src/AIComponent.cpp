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
  cpFloat diff = 0.0;
  cpFloat product = cpvdot(*normal, *other_velocity);
  const double thr = 0.0001;
  if(product < -thr) {
    std::cout << "[" << this->getId() << ", other is moving towards me " << std::endl;
    diff = other_position->y - position->y;
    std::cout << "[" << this->getId() << ", other is moving towards me, diff :" << diff << " ]" << std::endl;
    impulse.y = diff;
  } else if(product > thr) {
    std::cout << "[" << this->getId() << ", other is moving away from me " << std::endl;
    diff = position->y - getScreenHeight()/2 - 30;
    diff = diff/std::abs(diff);
    impulse.y = diff;
  } else {
    std::cout << "[" << this->getId() << ", other is parallel to me " << std::endl;
    return;
  }
  
  
  /*std::cout << "[" << this->getId() << ", product : " << product;
  std::cout << ", normal: { " <<normal->x << "," << normal->y << " }, ";
  std::cout << "ov: {" << other_velocity->x << ", "<< other_velocity->y << " } ]" << std::endl;
  */
  if(std::abs(diff) > thr) {
    position->y = position->y + diff/std::abs(diff) * 5.0;
  }

  position->x = 10;
  Message msg;
  msg.type = PLAYER_POSITION;
  msg.payload = position;
  msg.id = this->getId();
  for(const auto& comp: *observers) {
    comp->onNotify(msg);
  }
  
}

void AIComponent::onNotify(Message& message) {
  ComponentId fromID = message.id;
  switch (message.type) {
    case OTHER_POSITION: {
      cpVect v = (cpVect&) *message.payload;
      std::cout << "["<< fromID << " -> "<< this->getId() << ", notify other position { " << v.x << ", " << v.y << " } ]" << std::endl;
      other_position->x = v.x;
      other_position->y = v.y;
      break;
    }
      
    case OTHER_VELOCITY: {
      cpVect v = (cpVect&) *message.payload;
      std::cout << "["<< fromID << " -> "<< this->getId() << ", notify other velocity { " << v.x << ", " << v.y << " } ]" << std::endl;
      other_velocity->x = v.x;
      other_velocity->y = v.y;
      break;
    }
      
    case PLAYER_POSITION: {
      cpVect v = (cpVect&) *message.payload;
      std::cout << "["<< fromID << " -> "<<  this->getId() << ", notify player position { " << v.x << ", " << v.y << " } ]" << std::endl;
      position->x = v.x;
      position->y = v.y;
      break;
    }
      
    case PLAYER_VELOCITY: {
      cpVect v = (cpVect&) *message.payload;
      std::cout << "["<< fromID << " -> "<< this->getId() << ", notify player velocity { " << v.x << ", " << v.y << " } ]" << std::endl;
      velocity->x = v.x;
      velocity->y = v.y;
      break;
    }
    
    case NORMAL_VECTOR: {
      cpVect v = (cpVect&) *message.payload;
      if(v.x == 0 && v.y == 0) {
        return;
      }
      std::cout << "["<< fromID << " -> "<< this->getId() << ", notify normal vector { " << v.x << ", " << v.y << " } ]" << std::endl;
      normal->x = v.x;
      normal->y = v.y;
      break;
    }
      
    default:
      break;
  }
}
