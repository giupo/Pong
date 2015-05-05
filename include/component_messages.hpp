#ifndef __COMPONENT_MESSAGES_HPP__
#define __COMPONENT_MESSAGES_HPP__

#include "component_types.hpp"

enum PlayerMessages {
  PLAYER_UP = 2000,
  PLAYER_DOWN,
  PLAYER_LEFT,
  PLAYER_RIGHT,
  PLAYER_POSITION,
  PLAYER_VELOCITY,
  OTHER_POSITION,
  OTHER_VELOCITY,
  PLAYER_IMPULSE,
  NORMAL_VECTOR
};

typedef struct Message {
  ComponentId id;
	int type;
	void* payload;
} Message;

#endif
