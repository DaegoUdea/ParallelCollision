#ifndef SRC_GAME_PROPERTIES_H_
#define SRC_GAME_PROPERTIES_H_

#include <SDL2/SDL.h>

class GameProperties {

public:
  static GameProperties* getInstance();

  float fps;
  float deltaTime;
  float num_threads;
  float is_collision_on;

protected:
  GameProperties();
  ~GameProperties();

private:
  static GameProperties* _instance;

};

#endif  // SRC_GAME_PROPERTIES_H_
