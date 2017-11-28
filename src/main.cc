#include "game_engine.h"
#include "initstate.h"
#include <stdio.h>
#include "game_properties.h"

int main(int argc, char *argv[]) {
  GameProperties* properties = GameProperties::getInstance();

  if (argc != 2){
    properties->num_threads = 1;
  } else {
    properties->num_threads = atoi(argv[1]);
  }

  properties->is_collision_on = false;
  GameEngine game;
  game.change_state(InitState::Instance());
  game.execute();
  return 0;
}
