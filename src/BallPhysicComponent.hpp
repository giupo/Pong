//
//  BallPhysicComponent.h
//  Pong
//
//  Created by Giuseppe Acito on 04/05/15.
//  Copyright (c) 2015 CoreDumper. All rights reserved.
//

#ifndef __Pong__BallPhysicComponent__
#define __Pong__BallPhysicComponent__

#include "physic_comp.hpp"

class BallPhysicComponent : public PhysicsComponent {
public:
  BallPhysicComponent() {
    body = NULL;
    shape = NULL;
  }
  
  BallPhysicComponent(Actor* actor) {
    body = NULL;
    shape = NULL;
  }
  
  ~BallPhysicComponent() {
    std::cout << "Shutting down Physics...";
    this->destroy();
    std::cout << "Done" << std::endl;
  }
  
  virtual void init(XMLNode *node) {
    PhysicsComponent::init(node);
  }
  virtual void destroy() {
    PhysicsComponent::destroy();
  }
  
  virtual void update(double time) {
    PhysicsComponent::update(time);
    Message msg;
    msg.payload = this;
    msg.type = BALL_POSITION;
    for(const auto& comp : *observers) {
      comp->onNotify(msg);
    }
  }
  
  virtual void onNotify(Message &message) {
    
  }
};

#endif /* defined(__Pong__BallPhysicComponent__) */
