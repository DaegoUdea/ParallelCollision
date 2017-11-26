#include "vector2.h"
#include <cmath>

Vector2::Vector2() {
  x = 0.f;
  y = 0.f;
}

Vector2::Vector2(int x, int y) {
  this->x = x;
  this->y = y;
}

Vector2* Vector2::lerp(Vector2* from, Vector2* to, float percent) {
  float x, y = 0;
  x = ((1.f-percent) * from->getX()) + (percent * to->getX());
  y = ((1.f-percent) * from->getY()) + (percent * to->getY());

  x = floor(x + 0.5);
  y = floor(y + 0.5);
  return new Vector2(x, y);
}

void Vector2::add(Vector2* vector1, Vector2* vector2, Vector2* out) {
    out->setX(vector1->getX() + vector2->getX());
    out->setY(vector1->getY() + vector2->getY());
}

void Vector2::substract(Vector2* vector1, Vector2* vector2, Vector2* out) {
  out->setX(vector1->getX() - vector2->getX());
  out->setY(vector1->getY() - vector2->getY());
}

void Vector2::dot(Vector2* vector1, Vector2* vector2, float* scalar) {
  (*scalar) = (vector1->getX() * vector2->getX()) + (vector1->getY() * vector2->getY());
}

// Setters
void Vector2::setX(float new_x) {
  x = new_x;
}

void Vector2::setY(float new_y) {
  y = new_y;
}

// Getters
float Vector2::getX() {
  return x;
}

float Vector2::getY() {
  return y;
}
