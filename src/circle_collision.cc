#include "circle_collision.h"
#include "circle.h"
#include "vector2.h"
#include "math.h"
#include <iostream>
#include "game_properties.h"


CircleCollision::CircleCollision() {

}

CircleCollision::~CircleCollision() {

}

bool CircleCollision::check_collision(GameObject* object1, GameObject* object2, float* t) {
  GameProperties* properties = GameProperties::getInstance();
  Vector2 pos;
  Vector2 vel;
  Vector2 vel1;
  Vector2 vel2;
  float r, a, b, c, d;

  Vector2::substract(object1->getPosition(), object1->getOldPosition(), &vel1);
  Vector2::substract(object2->getPosition(), object2->getOldPosition(), &vel2);

  Vector2::substract(object1->getPosition(), object2->getPosition(), &pos);
  Vector2::substract(&vel1, &vel2, &vel);
  r = (object1->getWidth() / 2) + (object2->getWidth() / 2);

  Vector2::dot(&pos, &pos, &c);
  c = c - (r*r);
  if (c < 0.0f) {
    (*t) = 0.0f;
    return true;
  }

  Vector2::dot(&vel, &vel, &a);
  Vector2::dot(&vel, &pos, &b);
  if (b >= 0.0f) {
    return false;
  }

  d = (b*b) - a*c;
  if (d < 0.0f) {
    return false;
  }

  float t1, t2;

  t1 = (-b - sqrt(d)) / a;
  t2 = (-b + sqrt(d)) / a;

  if (t1 < t2) {
    (*t) = t1;
  } else {
    (*t) = t2;
  }

  return true;
}
