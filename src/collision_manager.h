#ifndef SRC_COLLISION_MANAGER_H_
#define SRC_COLLISION_MANAGER_H_

#include "gameobject.h"
#include <SDL2/SDL.h>
#include <vector>

class CollisionManager {
public:
  CollisionManager();
  void handle_collissions();
  void addGameObject(GameObject* gameObject);

private:
  std::vector<GameObject*> gameObjectList;
};

#endif  // SRC_COLLISION_MANAGER_H_
