#ifndef SRC_PHYSICS_MANAGER_H_Collision
#define SRC_PHYSICS_MANAGER_H_

#include "gameobject.h"
#include <SDL2/SDL.h>
#include <vector>
#include "rect_collision.h"
#include "circle_collision.h"

class PhysicsManager {
public:
  PhysicsManager();
  void handle_movement();
  void handle_collissions();
  void addStaticGameObject(GameObject* gameObject);
  void addDynamicGameObject(GameObject* gameObject);

private:
  std::vector<GameObject*> staticObjects;
  std::vector<GameObject*> dynamicObjects;
  RectCollision* rectCollision;
  CircleCollision* circleCollision;
};

#endif  // SRC_PHYSICS_MANAGER_H_
