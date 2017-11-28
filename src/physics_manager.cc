#include "physics_manager.h"
#include "collision.h"
#include "rect_collision.h"
#include "circle_collision.h"
#include <iostream>
#include <omp.h>
#include "game_properties.h"

PhysicsManager::PhysicsManager() {
  rectCollision = new RectCollision();
  circleCollision = new CircleCollision();
}

void PhysicsManager::handle_movement() {
  int size = dynamicObjects.size();
  int i = 0;
  GameObject* object;

  for (i = 0; i < size; i++) {
    object = (GameObject*)dynamicObjects.at(i);
    object->move();
  }
}

void PhysicsManager::handle_collissions() {
  GameProperties* properties = GameProperties::getInstance();
  int sizeStatic = staticObjects.size();
  int sizeDynamic = dynamicObjects.size();
  float t = 0;
  int i, j = 0;

  GameObject* object1;
  GameObject* object2;

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

  if (properties->is_collision_on) {
    for (i = 0; i < sizeDynamic; i++) {
      object1 = (GameObject*)dynamicObjects.at(i);
      for (j = 0; j < sizeDynamic; j++) {
        object2 = (GameObject*)dynamicObjects.at(j);

        if (object1 != object2) {
          if (circleCollision->check_collision(object1, object2, &t)) {
            Vector2* oldPos;
            Vector2* pos;
            Vector2* vel;

            if (t <= 1.f) {

              oldPos = object1->getOldPosition();
              pos = object1->getPosition();
              vel = object1->getVelocity();
              pos->setX(oldPos->getX() + (vel->getX() * properties->deltaTime * t));
              pos->setY(oldPos->getY() + (vel->getY() * properties->deltaTime * t));

              vel->setX(-(vel->getX()));
              vel->setY(-(vel->getY()));
            }
          }
        }
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
