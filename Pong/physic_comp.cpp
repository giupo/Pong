#include "physic_comp.hpp"

#include "chipmunk.h"
#include "physic_engine.hpp"
#include "locator.hpp"
#include "util_functions.h"
#include "game.hpp"
#include "BallPhysicComponent.hpp"

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
  
  cpBodySetPos(body, {x, y});
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
  if(nullptr != normal) {
    delete normal;
  }
}

inline void PhysicsComponent::update(double time) {
  cpVect position = getPosition();
  //Vect vel = getVelocity();
  std::cout << "[" << owner->getID() << ", ";
  std::cout << owner->getName() << "] position : ";
  std::cout << position.x << ", " << position.y << std::endl;
  
  if( position.x < 0 ) {
    position.x = 0;
  }
  
  if( position.x > Game::width ) {
    position.x = Game::width;
  }
  
  if( position.y < 0 ) {
    position.y = 0;
  }
  
  if( position.y > Game::height ) {
    position.y = Game::height;
  }
  
  Message msg;
  msg.type = PLAYER_POSITION;
  
  msg.payload = (void*) &position;
  
  for(const auto& comp: *observers) {
    comp->onNotify(msg);
  }
}

Vect PhysicsComponent::getPosition() const {
	Vect pos = cpBodyGetPos(body);
  return pos;
}

Vect PhysicsComponent::getVelocity() const {
	Vect vel = cpBodyGetVel(body);
	return vel;
}

void PhysicsComponent::onNotify(Message &message) {
  switch(message.type) {
    case PLAYER_POSITION: {
      cpVect* v = (cpVect*) message.payload;
      v->x = 0;
      cpBodyApplyForce(body, *v, getPosition());
      break;
    }
    case BALL_POSITION: {
      BallPhysicComponent* pc = (BallPhysicComponent*) message.payload;
      cpVect ballVelocity = pc->getVelocity();
      float product = normal->x * ballVelocity.x + normal->y * ballVelocity.y;
      ForwardedMessage fmsg = {message, this};
      this->owner->forward(fmsg);
      if(product < 0) {
        // the ball is coming!!!
        // go up
      } else {
        // go center.
      }
      break;
    }
    default: {
      break;
    }
  }
}