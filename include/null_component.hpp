//
//  Header.h
//  Pong
//
//  Created by Giuseppe Acito on 19/04/15.
//  Copyright (c) 2015 CoreDumper. All rights reserved.
//

#ifndef Pong_Null_Component_h
#define Pong_Null_Component_h

#include "component.hpp"
#include "tinyxml2.h"

using namespace tinyxml2;

class NullComponent : public GameComponent {
public:
  virtual void init(XMLNode *node);
  virtual void destroy();
  virtual void update(double time);
  
  static NullComponent& getInstance()
  {
    static NullComponent instance; // Guaranteed to be destroyed.
    // Instantiated on first use.
    return instance;
  }
private:
  NullComponent() {};                   // Constructor? (the {} brackets) are needed here.

  NullComponent(NullComponent const&) = delete;
  void operator=(NullComponent const&)  = delete;
};

#endif
