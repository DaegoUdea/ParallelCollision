#ifndef SRC_RECT_COLLISION_H_
#define SRC_RECT_COLLISION_H_

#include <SDL2/SDL.h>
#include "gameobject.h"
#include "collision.h"

class RectCollision : public Collision {
public:
  RectCollision();
  ~RectCollision();
  bool check_collision(GameObject* object1, GameObject* object2, float* t);
protected:

};

#endif  // SRC_RECT_COLLISION_H_
