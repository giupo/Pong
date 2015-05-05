#include "input_component.hpp"
#include <SDL2/SDL.h>
#include "tinyxml2.h"
#include "component_messages.hpp"
#include <iostream>
#include "Game.hpp"
using namespace tinyxml2;

void InputComponent::init(XMLNode *node) {
  id = (ComponentId) atoi(node->ToElement()->Attribute("id"));
  std::cout << "There are" <<  SDL_NumJoysticks() << " joysticks available" << std::endl;
  
  if(NULL == SDL_JoystickName(0)) {
    std::cout << "Default joystick (index 0) is Unknown" << std::endl;
  } else {
    std::cout << "Default joystick (index 0) is " << SDL_JoystickName(0) << std::endl;
    
  }
  accelerometer = SDL_JoystickOpen(0);
  if (accelerometer == NULL) {
    std::cout << "Could not open joystick (accelerometer)" << std::endl;
  }
}

void InputComponent::destroy() {
  SDL_JoystickClose(accelerometer);
}


void InputComponent::update(double time) {
  Sint16 ax = SDL_JoystickGetAxis(accelerometer, 0);
  Sint16 ay = SDL_JoystickGetAxis(accelerometer, 1);
  
  Message msg;
  msg.type = PLAYER_POSITION;
  msg.id = this->getId();
  cpVect position = { double(ax)/1000, double(ay)/1000 };
  msg.payload = (void*) &position;
  
  for(const auto& comp: *observers) {
    comp->onNotify(msg);
  }
}
