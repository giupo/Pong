#ifndef __COMPONENT_HPP__
#define __COMPONENT_HPP__

#include "tinyxml2.h"
#include <vector>
#include "component_messages.hpp"

using namespace tinyxml2;

class Actor;

typedef unsigned long ComponentId;

class GameComponent {
protected:
  Actor* owner;
  ComponentId id;
  std::vector<GameComponent*> *observers;
  
public:
  
  GameComponent() {
    observers = new std::vector<GameComponent*>();
  }
  
  ~GameComponent() {
    delete observers;
  }
  
  void setOwner(Actor* owner) {
    this->owner = owner;
  }
  
  ComponentId getId() {
    return id;
  }
  
  virtual void init( XMLNode *node ) =0;
  virtual void reset() {
  }
  virtual void post_init() {
  }
	virtual void destroy() =0;
	virtual void update( double time ) =0;
	
  virtual void addObserver(GameComponent* comp) {
    observers->push_back(comp);
  }
  
  virtual void onNotify(Message& message) {
  }
};

#endif
