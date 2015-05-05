#ifndef __PHYSIC_ENGINE_HPP__
#define __PHYSIC_ENGINE_HPP__

#include "chipmunk.h"
#include "tinyxml2.h"
#include "physic_comp.hpp"
#include "util_functions.h"

using namespace tinyxml2;

class PhysicEngine {
private:
	cpSpace *space;
  static const unsigned int MAX_COMPONENTS = 10;
  PhysicsComponent components[MAX_COMPONENTS];
  unsigned int activeComponents;
  
  static cpBool collisionDetection(cpArbiter* arb, cpSpace* space, void* data) {
    cpBody *a;
    cpBody *b;
    cpArbiterGetBodies(arb, &a, &b);
    cpVect bpos = cpBodyGetPos(b);
    cpVect apos = cpBodyGetPos(a);
    
    cout << apos.x << " " << apos.y << endl;
    cout << bpos.x << " " << bpos.y << endl;
    
    if(apos.x < 0) {
      SDL_Event event;
      event.type = SDL_USEREVENT;
      event.user.code = 2;
      SDL_PushEvent(&event);
      return false;
    } else if(apos.x > getScreenWidth()) {
      SDL_Event event;
      event.type = SDL_USEREVENT;
      event.user.code = 1;
      SDL_PushEvent(&event);
      return false;
    }
    return true;
  }
  
public:
	PhysicEngine() {
    activeComponents = 0;
		cpVect gravity = cpv(0, 0);
		this->space = cpSpaceNew();
		cpSpaceSetGravity(space, gravity);
	}

	~PhysicEngine() {
		cpSpaceFree( space );
  }

	cpSpace* getSpace() {
		return space;
	}

  PhysicsComponent* create();
 
  void addStaticSegment(int xi, int yi, int xf, int yf, double friction, double elasticity);
  void update(double time);
  void destroy();
  
  
};

#endif
