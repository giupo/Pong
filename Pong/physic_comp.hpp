#ifndef __PHYSICS_COMP_HPP__
#define __PHYSICS_COMP_HPP__

#include "actor.hpp"
#include "component_messages.hpp"

#include "tinyxml2.h"
#include <include_chipmunk/chipmunk.h>
#include <iostream>
#include "data_structs.hpp"
#include "render_component.hpp"

using namespace tinyxml2;

class Actor;
class RenderComponent;

class PhysicsComponent : public GameComponent {
protected:
  cpBody* body;
	cpShape* shape;
  cpVect* normal;
public:
  
  PhysicsComponent() {
    body = NULL;
    shape = NULL;
  }
  
	PhysicsComponent(Actor* actor) {
    body = NULL;
    shape = NULL;
  }
  
	~PhysicsComponent() {
		std::cout << "Shutting down Physics...";
		this->destroy();
		std::cout << "Done" << std::endl;
	}

  virtual void init(XMLNode *node);
	virtual void destroy();
	virtual void update(double time);
	virtual void onNotify(Message &message);


	Vect getPosition() const;
	Vect getVelocity() const;
  
};

#endif
