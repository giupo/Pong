#include <iostream>
#include "game.hpp"
#include "util_functions.h"

int main (int argc, char** argv) {
  // initialize Game
  Game game( getScreenWidth(), getScreenHeight() );
	game.init();
	game.loop();
  return 0;
}
