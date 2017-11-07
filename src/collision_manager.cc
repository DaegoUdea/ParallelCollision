#include "collision_manager.h"
#include "collision.h"
#include "rect_collision.h"
#include <iostream>

CollisionManager::CollisionManager() {

}

void CollisionManager::handle_collissions() {
  std::vector<GameObject*>::iterator object1;
  std::vector<GameObject*>::iterator object2;
  Collision* collision;

  for (object1 = gameObjectList.begin(); object1 != gameObjectList.end(); ++object1) {
    for (object2 = gameObjectList.begin(); object2 != gameObjectList.end(); ++object2) {
      if (object1 != object2) {
        collision = new RectCollision();
        if (collision->check_collision(*object1, *object2)) {
          (*object1)->onCollision(*object2);
          (*object2)->onCollision(*object1);
        }
      }
    }
  }
}

void CollisionManager::addGameObject(GameObject* gameObject) {
  gameObjectList.push_back(gameObject);
}
