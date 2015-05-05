#ifndef __COMPONENT_MESSAGES_HPP__
#define __COMPONENT_MESSAGES_HPP__
#include "component_types.hpp"
#include "component.hpp"

class GameComponent;

enum BallMessages {
  GOING_AWAY = 1000,
  BALL_COMING,
  BALL_POSITION
};

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

enum AIPlayerMessages {
  CENTER 
};

enum EVENTS {
  EVENTO_VITTORIA_1 = 1213145,
  EVENTO_VITTORIA_2
};

typedef struct Message {
  ComponentId id;
	int type;
	void* payload;
} Message;

#endif
