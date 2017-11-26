#include "physics_manager.h"
#include "collision.h"
#include "rect_collision.h"
#include "circle_collision.h"
#include <iostream>

PhysicsManager::PhysicsManager() {

}

void PhysicsManager::handle_movement(float deltaTime) {
  int size = dynamicObjects.size();
  GameObject* object;

  // #pragma omp parallel for private(object)
  for (int i = 0; i < size; i++) {
    object = (GameObject*)dynamicObjects.at(i);
    object->move(deltaTime);
    handle_collissions(deltaTime);
  }
}

void PhysicsManager::handle_collissions(float deltaTime) {
  int sizeStatic = staticObjects.size();
  int sizeDynamic = dynamicObjects.size();

  Collision* collision;
  GameObject* object1;
  GameObject* object2;
  float t = 0;

  // #pragma omp parallel for private(collision, object1, object2)
  for (int i = 0; i < sizeDynamic; i++) {
    for (int j = 0; j < sizeStatic; j++) {
      object1 = (GameObject*)dynamicObjects.at(i);
      object2 = (GameObject*)staticObjects.at(j);

      if (object1 != object2) {
        collision = new RectCollision();
        if (collision->check_collision(object1, object2, &t)) {
          object1->onCollision(object2);
          object2->onCollision(object1);
        }
        delete collision;
      }
    }
  }

  collision = new CircleCollision();
  #pragma omp parallel for private(object1, object2)
  for (int i = 0; i < sizeDynamic; i++) {
    for (int j = 0; j < sizeDynamic; j++) {
      object1 = (GameObject*)dynamicObjects.at(i);
      object2 = (GameObject*)dynamicObjects.at(j);

      if (object1 != object2) {
        // collision = new CircleCollision();
        if (collision->check_collision(object1, object2, &t)) {
          Vector2* pos;
          Vector2* vel;

          if (t <= deltaTime) {
            /* code */
            pos = object1->getPosition();
            vel = object1->getVelocity();
            pos->setX(pos->getX() + (vel->getX() * (t - (1 * deltaTime))));
            pos->setY(pos->getY() + (vel->getY() *(t - (1 * deltaTime))));
            vel->setX(-(vel->getX()));
            vel->setY(-(vel->getY()));

            pos = object2->getPosition();
            vel = object2->getVelocity();
            pos->setX(pos->getX() + (vel->getX()* deltaTime *(t - (1 * deltaTime))));
            pos->setY(pos->getY() + (vel->getY()* deltaTime *(t - (1 * deltaTime))));
            vel->setX(-(vel->getX()));
            vel->setY(-(vel->getY()));
          }

          // object1->onCollision(object2);
          // object2->onCollision(object1);
        }
        // delete collision;
      }
    }
  }
}

void PhysicsManager::addStaticGameObject(GameObject* gameObject) {
  staticObjects.push_back(gameObject);
}

void PhysicsManager::addDynamicGameObject(GameObject* gameObject) {
  dynamicObjects.push_back(gameObject);
}
