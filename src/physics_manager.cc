#include "physics_manager.h"
#include "collision.h"
#include "rect_collision.h"
#include <iostream>

PhysicsManager::PhysicsManager() {

}

void PhysicsManager::handle_movement(float deltaTime) {
  int size = gameObjectList.size();
  GameObject* object;

  #pragma omp parallel for private(object)
  for (int i = 0; i < size; i++) {
    object = (GameObject*)gameObjectList.at(i);
    object->move(deltaTime);
  }
}

void PhysicsManager::handle_collissions() {
  int size = gameObjectList.size();
  Collision* collision;
  GameObject* object1;
  GameObject* object2;

  // #pragma omp parallel for private(collision, object1, object2)
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      object1 = (GameObject*)gameObjectList.at(i);
      object2 = (GameObject*)gameObjectList.at(j);

      if (object1 != object2) {
        collision = new RectCollision();
        if (collision->check_collision(object1, object2)) {
          object1->onCollision(object2);
          object2->onCollision(object1);
        }
        delete collision;
      }
    }
  }
}

void PhysicsManager::addGameObject(GameObject* gameObject) {
  gameObjectList.push_back(gameObject);
}
