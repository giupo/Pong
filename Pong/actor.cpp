#include "actor.hpp"
#include "component.hpp"
#include "locator.hpp"
#include "tinyxml2.h"
#include <iostream>
#include <map>
#include "component_types.hpp"
#include "null_component.hpp"
#include "AIComponent.hpp"

using namespace tinyxml2;
using namespace std;

map<ComponentId, GameComponent*> Actor::compMap;

void Actor::init(XMLNode* node) {
  this->name = string(node->ToElement()->Attribute("name"));
  this->id = atoi(node->ToElement()->Attribute("id"));
  XMLElement* compdef = node->FirstChildElement();
  while(compdef) {
    const char* name = compdef->Name();
    cout << "initializing " << name << ", id:" << id << endl;
    GameComponent* comp;
    switch(hashComponentName(name)) {
      case NULL_COMPONENT: {
        comp = &NullComponent::getInstance();
        break;
      }
        
      case INPUT_COMPONENT: {
        comp = Locator::getBrainEngine()->createInputComponent();
        break;
      }
        
      case PHYSIC_COMPONENT: {
        PhysicEngine *engine = Locator::getPhysicEngine();
        comp = engine->create();
        if(NULL == comp) {
          cout << "Warning, you should raise your MAX_COMPONENTS constant" << endl;
        }
        break;
      }
        
      case BALL_PHYSIC_COMPONENT: {
        
        break;
      }
      
      case RENDER_COMPONENT: {
        comp = Locator::getRenderEngine()->create();
        break;
      }
        
      case AI_COMPONENT: {
        comp = Locator::getBrainEngine()->createAIComponent();
        break;
      }
        
      default:
        comp = &NullComponent::getInstance();
    }
    comp->setOwner(this);
    comp->init(compdef);
    components->push_back(comp);
    compMap[comp->getId()] = comp;
    cout << compdef->Name() << endl;
    compdef = compdef->NextSiblingElement();
  }
}

void Actor::update(double time) {
  for(const auto& c: *components) {
    c->update(time);
  }
}

void Actor::destroy() {
  for(const auto& c: *components) {
    c->destroy();
  }
}

void Actor::forward( ForwardedMessage &msg) {
  for(const auto& comp: *components) {
    if(msg.sender->getId() != comp->getId()) {
      comp->onNotify(msg.message);
    }
  }
}
