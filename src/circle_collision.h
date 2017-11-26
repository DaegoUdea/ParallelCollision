#ifndef SRC_CIRCLE_COLLISION_H_
#define SRC_CIRCLE_COLLISION_H_

#include <SDL2/SDL.h>
#include "gameobject.h"
#include "collision.h"

class CircleCollision : public Collision {
public:
  CircleCollision();
  ~CircleCollision();
  bool check_collision(GameObject* object1, GameObject* object2, float* t);
protected:

};

#endif  // SRC_CIRCLE_COLLISION_H_
