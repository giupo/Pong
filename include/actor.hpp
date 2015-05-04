#ifndef __ACTOR_HPP__
#define __ACTOR_HPP__

#include <map>
#include <vector>
#include <string>
#include "component.hpp"
#include "component_messages.hpp"
#include "input_component.hpp"
#include "physic_comp.hpp"
#include "tinyxml2.h"
#include "render_component.hpp"

using namespace std;
using namespace tinyxml2;

class GameComponent;

typedef shared_ptr<GameComponent*> StrongGameComponent;
typedef weak_ptr<GameComponent*> WeakGameComponent;
typedef unsigned int ActorId;
typedef vector<StrongGameComponent> GameComponentList;

class InputComponent;
class PhysicsComponent;
class RenderComponent;

class Actor {
public:
	Actor(): id(0), name("Unknown Actor") {
    components = new std::vector<GameComponent*>();
	}

	Actor(int id_, string name_): id(id_), name(name_) {
    components = new std::vector<GameComponent*>();
	}

	~Actor() {
    this->destroy();
	}

	void init(XMLNode *node);
	void update(double time);
  void destroy();
	
	ActorId getID() const {
		return this->id;
	}

	string getName() const {
		return this->name;
	}
	
  static map<ComponentId, GameComponent*> compMap;
  
protected:
	int id;
  std::string name;
  private:
  std::vector<GameComponent*> *components;
};

#endif
