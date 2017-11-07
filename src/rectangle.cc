#include "rectangle.h";
#include "vector2.h"
#include <iostream>

Rectangle::Rectangle(float x, float y, float w, float h) {
  texture = NULL;
  oldPosition = new Vector2();
  position = new Vector2();
  velocity = new Vector2();

  oldPosition->setX(x);
  oldPosition->setY(y);

  position->setX(x);
  position->setY(y);

  velocity->setX(0);
  velocity->setY(0);

  width = w;
  height = h;

  sdl_rectangle = {(int)x, (int)y, (int)w, (int)h};

  init();
}

void Rectangle::init() {

}

void Rectangle::move(float deltaTime) {
  oldPosition->setX(position->getX());
  oldPosition->setY(position->getY());

  position->setX(position->getX() + (velocity->getX() * deltaTime));
  position->setY(position->getY() + (velocity->getY() * deltaTime));
}

void Rectangle::setDimension(float width, float height) {
  this->width = width;
  this->height = height;
}

SDL_Rect* Rectangle::getSDLRectangle() {
  return &sdl_rectangle;
}

void Rectangle::onCollision(GameObject* object) {
  position->setX(oldPosition->getX());
  position->setY(oldPosition->getY());
  // std::cout << "I did collide with something" << '\n';
}

// Setters
void Rectangle::setPosition(Vector2* position) {
  oldPosition->setX(this->position->getX());
  oldPosition->setY(this->position->getY());

  delete[] this->position;
  this->position = position;
}

void Rectangle::refreshPosition() {
  oldPosition->setX(position->getX());
  oldPosition->setY(position->getY());
}

void Rectangle::setWidth(float width) {
  this->width = width;
}
void Rectangle::setHeight(float height) {
  this->height = height;
}

void Rectangle::setVelocity(Vector2* velocity) {
  this->velocity = velocity;
}

void Rectangle::setTexture(SDL_Texture* texture) {
  this->texture = texture;
}

// Getters
Vector2* Rectangle::getPosition() {
  return position;
}

Vector2* Rectangle::getVelocity() {
  return velocity;
}

float Rectangle::getWidth() {
  return width;
}

float Rectangle::getHeight() {
  return height;
}

SDL_Texture* Rectangle::getTexture() {
  return texture;
}
