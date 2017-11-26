#include "physics_manager.h"
#include "collision.h"
#include "rect_collision.h"
#include "circle_collision.h"
#include <iostream>
#include <omp.h>

PhysicsManager::PhysicsManager() {
  rectCollision = new RectCollision();
  circleCollision = new CircleCollision();
}

void PhysicsManager::handle_movement(float deltaTime) {
  int size = dynamicObjects.size();
  int i = 0;
  GameObject* object;

  int local_i, local_j, local_n;
  int my_rank = omp_get_thread_num();
  int thread_count = omp_get_num_threads();

  local_n = size / thread_count;

  // #pragma omp parallel for private(object, i)
  for (i = 0; i < size; i++) {
    object = (GameObject*)dynamicObjects.at(i);
    object->move(deltaTime);
  }
}

void PhysicsManager::handle_collissions(float deltaTime) {
  int sizeStatic = staticObjects.size();
  int sizeDynamic = dynamicObjects.size();
  float t = 0;
  int i, j = 0;

  GameObject* object1;
  GameObject* object2;

  int local_i, local_j, local_n, local_m;
  int my_rank = omp_get_thread_num();
  int thread_count = omp_get_num_threads();

  local_n = sizeDynamic / thread_count;

  #pragma omp parallel for private(i,j,object1,object2)
  for (i = 0; i < sizeStatic; i++) {
    object1 = (GameObject*)staticObjects.at(i);
    for (j = 0; j < sizeDynamic; j++) {
      object2 = (GameObject*)dynamicObjects.at(j);

      if (object1 != object2) {
        if (rectCollision->check_collision(object1, object2, &t)) {
          object1->onCollision(object2);
          object2->onCollision(object1);
        }
      }
    }
  }

  // #pragma omp parallel for private(i,j,object1,object2)
  // for (i = 0; i < sizeDynamic; i++) {
  //   object1 = (GameObject*)dynamicObjects.at(i);
  //   for (j = 0; j < sizeDynamic; j++) {
  //     object2 = (GameObject*)dynamicObjects.at(j);
  //
  //     if (object1 != object2) {
  //       if (circleCollision->check_collision(object1, object2, &t)) {
  //         Vector2* pos;
  //         Vector2* vel;
  //
  //         if (t <= deltaTime) {
  //           pos = object1->getPosition();
  //           vel = object1->getVelocity();
  //           pos->setX(pos->getX() + (vel->getX() * (t - (1 * deltaTime))));
  //           pos->setY(pos->getY() + (vel->getY() *(t - (1 * deltaTime))));
  //           vel->setX(-(vel->getX()));
  //           vel->setY(-(vel->getY()));
  //
  //           pos = object2->getPosition();
  //           vel = object2->getVelocity();
  //           pos->setX(pos->getX() + (vel->getX()* deltaTime *(t - (1 * deltaTime))));
  //           pos->setY(pos->getY() + (vel->getY()* deltaTime *(t - (1 * deltaTime))));
  //           vel->setX(-(vel->getX()));
  //           vel->setY(-(vel->getY()));
  //         }
  //       }
  //     }
  //   }
  // }

}

void PhysicsManager::addStaticGameObject(GameObject* gameObject) {
  staticObjects.push_back(gameObject);
}

void PhysicsManager::addDynamicGameObject(GameObject* gameObject) {
  dynamicObjects.push_back(gameObject);
}
