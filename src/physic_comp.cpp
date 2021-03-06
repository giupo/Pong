#include "physic_comp.hpp"

#include "chipmunk.h"
#include "physic_engine.hpp"
#include "locator.hpp"
#include "util_functions.h"
#include "game.hpp"

void PhysicsComponent::init(XMLNode *node) {
  XMLElement *element = node->ToElement();
  id = (ComponentId) atoi(element->Attribute("id"));
  
  
  cpFloat nx = atof(element->Attribute("nx"));
  cpFloat ny = atof(element->Attribute("ny"));
  
  normal = new cpVect;
  normal->x = nx;
  normal->y = ny;
  
  cpFloat mass = atof(element->Attribute("mass"));
  cpFloat width = atof(element->Attribute("width"));
  cpFloat height = atof(element->Attribute("height"));
	cpFloat radius = atof(element->Attribute("radius"));
  cpFloat friction = atof(element->Attribute("friction"));
  cpFloat elasticity = atof(element->Attribute("elasticity"));
	cpSpace *space = Locator::getPhysicEngine()->getSpace();
	
  std::string type(element->Attribute("type"));
  //TODO: refactor sta merda.
  if(string("box").compare(type) == 0) {
    body = cpBodyNew(mass, cpMomentForBox(mass, width, height));
    shape = cpBoxShapeNew(body, width, height);
  } else if (string("ball").compare(type) == 0) {
    cpVect offset = { width/2, height/2 };
    body = cpBodyNew(mass, cpMomentForCircle(mass, radius, radius, offset));
    shape = cpCircleShapeNew(body, radius, offset);
    shape->collision_type = 0;
  }
  
  cpShapeSetElasticity(shape, elasticity);
  cpShapeSetFriction(shape, friction);
	cpSpaceAddBody(space, body);
	cpSpaceAddShape(space, shape);
  
  cpFloat x = atof(element->Attribute("x"));
  cpFloat y = atof(element->Attribute("y"));
  cout << "x : " << x << endl;
  x = denormalizeX(x);
  cout << "x : " << x << endl;
  cout << "y : " << y << endl;
  y = denormalizeY(y);
  cout << "y : " << y << endl;
  startPosition = { x, y };
  cpBodySetPos(body, startPosition);
  cpBodySetVel(body, {0, 0});
}

void PhysicsComponent::destroy() {
	if(NULL != body) {
		cpBodyFree(body);
		body = NULL;
	}
	if(NULL != shape) {
		cpShapeFree(shape);
		shape = NULL;
	}
  if(NULL != normal) {
    delete normal;
  }
}

inline void PhysicsComponent::update(double time) {
  refreshStatus();
}

Vect PhysicsComponent::getPosition() const {
	Vect pos = cpBodyGetPos(body);
  return pos;
}

Vect PhysicsComponent::getVelocity() const {
	Vect vel = cpBodyGetVel(body);
	return vel;
}

inline void PhysicsComponent::onNotify(Message &message) {
  switch(message.type) {
    case PLAYER_IMPULSE: {
      cpVect impulse = (cpVect &) *message.payload;
      std::cout <<"[" << message.id << " -> " << this->getId() << ", apply impulse: { " << impulse.x << ", " << impulse.y << "} ]" <<  std::endl;
      this->apply(impulse);
      break;
    }
      
    case PLAYER_POSITION: {
      cpVect position = (cpVect &) *message.payload;
      std::cout <<"[" << message.id << " -> " << this->getId() << ", set position: { " << position.x << ", " << position.y << "} ]" <<  std::endl;
      cpBodySetPos( body, position );
    }
    
    default: {
      break;
    }
  }
}


void PhysicsComponent::apply(const cpVect& j, const cpVect& r) {
  cpBodyApplyImpulse(body, j, r);
}

void PhysicsComponent::post_init() {
  refreshStatus();
}


void PhysicsComponent::reset() {
  cpBodySetPos(body, startPosition);
  cpBodySetVel(body, cpvzero);
}