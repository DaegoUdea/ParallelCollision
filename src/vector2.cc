#include "vector2.h"

Vector2::Vector2() {
  x = 0.f;
  y = 0.f;
}

Vector2::Vector2(int x, int y) {
  this->x = x;
  this->y = y;
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
