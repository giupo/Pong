#ifndef __COMPONENT_MESSAGES_HPP__
#define __COMPONENT_MESSAGES_HPP__

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
  PLAYER_POSITION
};

enum AIPlayerMessages {
  CENTER 
};

typedef struct Message {
	int type;
	void* payload;
} Message;

typedef struct ForwardedMessage {
  ForwardedMessage(Message& msg, GameComponent* cmp) :
    message(msg),
    sender(cmp) {
    
  }
  Message& message;
  GameComponent *sender;
} ForwardedMessage;

#endif
