#ifndef SRC_COLLISION_H_
#define SRC_COLLISION_H_

#include <SDL2/SDL.h>
#include "gameobject.h"

class Collision {
public:
  Collision() {};
  ~Collision() {};
  virtual bool check_collision(GameObject* object1, GameObject* object2) = 0;

protected:

};

#endif  // SRC_COLLISION_H_
