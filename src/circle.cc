#include "circle.h";
#include "vector2.h"
#include <iostream>
#include "game_properties.h"

Circle::Circle(float x, float y, float r) {
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

  width = r * 2;
  height = r * 2;
  radius = r;

  init();
}

void Circle::init() {

}

void Circle::move() {
  GameProperties* properties = GameProperties::getInstance();
   oldPosition->setX(position->getX());
   oldPosition->setY(position->getY());

   position->setX(position->getX() + (velocity->getX() * properties->deltaTime));
   position->setY(position->getY() + (velocity->getY() * properties->deltaTime));
}

void Circle::setDimension(float width, float height) {
  this->width = width;
  this->height = height;
}

void Circle::onCollision(GameObject* object) {
  position->setX(oldPosition->getX());
  position->setY(oldPosition->getY());

  velocity->setX(-(velocity->getX()));
  velocity->setY(-(velocity->getY()));
}

// Setters
void Circle::setPosition(Vector2* position) {
  oldPosition->setX(this->position->getX());
  oldPosition->setY(this->position->getY());

    delete this->position;
    this->position = position;
}

void Circle::setOldPosition(Vector2* oldPosition) {
    delete this->oldPosition;
    this->oldPosition = oldPosition;
}

void Circle::refreshPosition() {
  oldPosition->setX(position->getX());
  oldPosition->setY(position->getY());
}

void Circle::setWidth(float width) {
  this->width = width;
}
void Circle::setHeight(float height) {
  this->height = height;
}

void Circle::setRadius(float radius) {
  this->radius = radius;
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

Vector2* Circle::getOldPosition() {
  return oldPosition;
}

Vector2* Circle::getVelocity() {
  return velocity;
}

float Circle::getWidth() {
  return width;
}

float Circle::getHeight() {
  return height;
}

float Circle::getRadius() {
  return radius;
}

SDL_Texture* Circle::getTexture() {
  return texture;
}
