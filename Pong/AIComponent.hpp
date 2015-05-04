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
  bool is_paused;
  Vect ball_position;
public:
  
  AIComponent() {
    is_paused = false;
  }
  ~AIComponent() {
    
  }
  virtual void init(XMLNode *node);
  virtual void destroy();
  virtual void update(double time);
  virtual void onNotify(Message& message);
};

#endif /* defined(__Pong__AIComponent__) */
