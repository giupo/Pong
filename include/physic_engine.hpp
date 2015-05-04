#ifndef __PHYSIC_ENGINE_HPP__
#define __PHYSIC_ENGINE_HPP__

#include "chipmunk/chipmunk.h"
#include "tinyxml2.h"
#include "physic_comp.hpp"

using namespace tinyxml2;

class PhysicEngine {
private:
	cpSpace *space;
  static const unsigned int MAX_COMPONENTS = 10;
  PhysicsComponent components[MAX_COMPONENTS];
  unsigned int activeComponents;
  
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
