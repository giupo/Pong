#include "physic_engine.hpp"
#include "chipmunk.h"
#include "physic_comp.hpp"

void PhysicEngine::update(double time) {	
  //cpVect g = cpSpaceGetGravity(space);
  //cout << "Gravity: x=" << g.x << ", y=" << g.y << endl;
  for(unsigned int i = 0; i < activeComponents; ++i ) {
    components[i].update(time);
  }
  cpSpaceStep( space , time );
}

void PhysicEngine::destroy() {
  for(unsigned int i = 0; i < activeComponents; ++i ) {
    components[i].destroy();
  }
}

PhysicsComponent* PhysicEngine::create() {
  if(activeComponents >= MAX_COMPONENTS) {
    return NULL;
  }
  return &components[activeComponents++];
}

void PhysicEngine::addStaticSegment(int xi, int yi, int xf, int yf, double friction, double elasticity) {
  cpBody* sb = cpBodyNewStatic();
  cpShape* segment = cpSegmentShapeNew(sb, cpv(xi, yi), cpv(xf, yf), 0);
  segment->collision_type = 1;
  cpShapeSetFriction(segment, friction);
  cpShapeSetElasticity(segment, elasticity);
  cpSpaceAddShape(space, segment);
  cpSpaceAddCollisionHandler(space, 0, 1, collisionDetection, NULL, NULL, NULL, NULL);
}