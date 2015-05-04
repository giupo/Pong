#ifndef __RENDER_COMPONENT_HPP__
#define __RENDER_COMPONENT_HPP__

#include "component.hpp"
#include "component_messages.hpp"
#include "actor.hpp"

#include "tinyxml2.h"
#include "physic_comp.hpp"
#include <SDL2/SDL.h>
#include <iostream>

using namespace tinyxml2;

class PhysicsComponent;

class RenderComponent : public GameComponent {
private:
	SDL_Texture* sprite;
	SDL_Rect rect;
	Actor* actor;
public:
  RenderComponent() {
    this->sprite = NULL;
    this->actor = NULL;
  }

	~RenderComponent() {
		this->destroy();
	}
	
	virtual void init(XMLNode* node);
	virtual void update(double time);
	virtual void destroy();
	virtual void onNotify(Message& message);
};

#endif
