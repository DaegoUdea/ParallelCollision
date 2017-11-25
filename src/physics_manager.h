#ifndef SRC_PHYSICS_MANAGER_H_Collision
#define SRC_PHYSICS_MANAGER_H_

#include "gameobject.h"
#include <SDL2/SDL.h>
#include <vector>

class PhysicsManager {
public:
  PhysicsManager();
  void handle_movement(float deltaTime);
  void handle_collissions();
  void addGameObject(GameObject* gameObject);

private:
  std::vector<GameObject*> gameObjectList;
};

#endif  // SRC_PHYSICS_MANAGER_H_
