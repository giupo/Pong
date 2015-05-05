//
//  AIComponent.h
//  Pong
//
//  Created by Giuseppe Acito on 19/04/15.
//  Copyright (c) 2015 CoreDumper. All rights reserved.
//

#ifndef __Pong__AIComponent__
#define __Pong__AIComponent__

#include "tinyxml2.h"
#include "component.hpp"
#include "data_structs.hpp"

class AIComponent : public GameComponent {
private:
  Vect* other_position;
  Vect* other_velocity;
  Vect* position;
  Vect* velocity;
  Vect* normal;
public:
  
  AIComponent() {
    other_position = new Vect;
    other_velocity = new Vect;
    position = new Vect;
    velocity = new Vect;
    normal = new Vect;
  }
  ~AIComponent() {
    delete other_velocity;
    delete other_position;
    delete position;
    delete normal;
    delete velocity;
  }
  
  virtual void init(XMLNode *node);
  virtual void destroy();
  virtual void update(double time);
  virtual void onNotify(Message& message);
  
  void up() {
    
  }
  
  void down() {
    
  }
  
  void center() {
    
  }
  
};

#endif /* defined(__Pong__AIComponent__) */
