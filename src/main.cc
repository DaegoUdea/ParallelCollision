#include "game_engine.h"
#include "initstate.h"

int main(int argc, char *argv[]) {
  GameEngine game;
  game.change_state(InitState::Instance());
  game.execute();
  return 0;
}
