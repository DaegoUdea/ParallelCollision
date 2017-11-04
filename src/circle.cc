#include "circle.h";
#include "vector2.h"

Circle::Circle() {
  init();
}

void Circle::init() {
  texture = NULL;
  position = new Vector2();
  velocity = new Vector2();

  position->setX(0);
  position->setY(0);

  velocity->setX(0);
  velocity->setY(0);

  width = 0;
  height = 0;
}

void Circle::move(float deltaTime) {
   position->setX(position->getX() + (velocity->getX() * deltaTime));
   position->setY(position->getY() + (velocity->getY() * deltaTime));
}

void Circle::setDimension(int width, int height) {
  this->width = width;
  this->height = height;
}

// Setters
void Circle::setPosition(Vector2* position) {
    this->position = position;
}

void Circle::setWidth(int width) {
  this->width = width;
}
void Circle::setHeight(int height) {
  this->height = height;
}

void Circle::setVelocity(Vector2* velocity) {
  this->velocity = velocity;
}

void Circle::setTexture(SDL_Texture* texture) {
  this->texture = texture;
}

// Getters
Vector2* Circle::getPosition() {
  return position;
}

Vector2* Circle::getVelocity() {
  return velocity;
}

int Circle::getWidth(int width) {
  return width;
}

int Circle::getHeight(int height) {
  return height;
}

SDL_Texture* Circle::getTexture() {
  return texture;
}
