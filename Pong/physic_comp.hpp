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
  cpVect startPosition;
  
public:
  
  PhysicsComponent() {
    body = NULL;
    shape = NULL;
    normal = NULL;
  }
  
	PhysicsComponent(Actor* actor) {
    body = NULL;
    shape = NULL;
    normal = NULL;
  }
  
	~PhysicsComponent() {
		std::cout << "Shutting down Physics...";
		this->destroy();
		std::cout << "Done" << std::endl;
	}

  virtual void init(XMLNode *node);
	virtual void destroy();
	virtual void update(double time);
  virtual void reset();
	virtual void onNotify(Message &message);
  virtual void post_init();
  virtual void apply(const cpVect& j,const cpVect& r);
  virtual void apply(const cpVect& j) {
    this->apply(j, cpvzero);
  }

	Vect getPosition() const;
	Vect getVelocity() const;
  
};

#endif
