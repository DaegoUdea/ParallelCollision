#include "circle.h";

Circle::Circle() {
  init();
}

void Circle::move() {

  x = x + vx;
  y = y + vy;
}

void Circle::init() {
  width = height = r = 20;
  x = old_x = 0;
  y = old_y = 0;
  vx = 0;
  vy = 0;
}

void Circle::setRadius(int radius) {
  r = width = height = radius;
}

int Circle::getRadius() {
  return r;
}

int Circle::getX() {
  return x;
}

int Circle::getY() {
  return y;
}

void Circle::setPosition(int new_x, int new_y) {
  x = new_x;
  y = new_y;
}

void Circle::setVelocity(int new_vx, int new_vy) {
  vx = new_vx;
  vy = new_vy;
}

void Circle::setTexture(SDL_Texture* tex) {
  texCircle = tex;
}

SDL_Texture* Circle::getTexture() {
  return texCircle;
}
