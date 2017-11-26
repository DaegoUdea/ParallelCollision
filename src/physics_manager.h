#ifndef SRC_PHYSICS_MANAGER_H_Collision
#define SRC_PHYSICS_MANAGER_H_

#include "gameobject.h"
#include <SDL2/SDL.h>
#include <vector>

class PhysicsManager {
public:
  PhysicsManager();
  void handle_movement(float deltaTime);
  void handle_collissions(float deltaTime);
  void addStaticGameObject(GameObject* gameObject);
  void addDynamicGameObject(GameObject* gameObject);

private:
  std::vector<GameObject*> staticObjects;
  std::vector<GameObject*> dynamicObjects;
};

#endif  // SRC_PHYSICS_MANAGER_H_
