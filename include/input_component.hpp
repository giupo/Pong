#ifndef __INPUT_COMPONENT_HPP__
#define __INPUT_COMPONENT_HPP__

#include "component.hpp"
#include "actor.hpp"
#include "tinyxml2.h"
#include "component_messages.hpp"
#include <SDL2/SDL.h>
#include "physic_comp.hpp"
#include <iostream>
#include <vector>

using namespace tinyxml2;

class Actor;
class PhysicsComponent;

class InputComponent : public GameComponent {
protected:
  SDL_Joystick *accelerometer;
public:
  std::shared_ptr<Actor*> owner;
	InputComponent() {
    if ( SDL_Init( SDL_INIT_GAMECONTROLLER  ) < 0 ) {
      printf( "Unable to init SDL: %s\n", SDL_GetError() );
      exit(1);
    }
	}
	
	~InputComponent() { }

	virtual void init( XMLNode* node );
	virtual void destroy();
	virtual void update( double time );
  
};

#endif
