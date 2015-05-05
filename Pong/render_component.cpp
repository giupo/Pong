#include "render_component.hpp"
#include "tinyxml2.h"
#include "locator.hpp"
#include "physic_comp.hpp"
#include <cstdlib>

using namespace tinyxml2;

void RenderComponent::init(XMLNode* node) {
  id = (ComponentId) atoi(node->ToElement()->Attribute("id"));
  std::string spriteName(node->ToElement()->Attribute("sprite"));
  std::cout << spriteName << std::endl;
  ResourceManager* rm = Locator::getResourceManager();
  sprite = rm->getSurface(spriteName);
  int w, h;
  SDL_QueryTexture( sprite, NULL, NULL, &w, &h );
  rect.w = w;
  rect.h = h;
}

inline void RenderComponent::update(double time) {
  SDL_Renderer* renderer = Locator::getRenderEngine()->getRenderer();
	SDL_RenderCopy( renderer, sprite, NULL, &rect );
}

void RenderComponent::destroy() {
  
}

void RenderComponent::onNotify( Message& message ) {
  switch( message.type ) {
    case PLAYER_POSITION: {
      cpVect& position = (cpVect &) *message.payload;
      rect.x = position.x;
      rect.y = position.y;
      break;
    }
    default: {
      break;
    }
  }
}
