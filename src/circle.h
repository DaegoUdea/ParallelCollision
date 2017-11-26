#ifndef SRC_CIRCLE_H_
#define SRC_CIRCLE_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "gameobject.h"
#include "vector2.h"

class Circle : public GameObject {
public:
  Circle(float x, float y, float r);

  void init();
  void move(float deltaTime);
  void setDimension(float width, float height);
  void onCollision(GameObject* object);

  // Setters
  void setPosition(Vector2* position);
  void refreshPosition();
  void setWidth(float width);
  void setHeight(float height);
  void setRadius(float radius);
  void setVelocity(Vector2* velocity);
  void setTexture(SDL_Texture* texture);

  // Getters
  Vector2* getPosition();
  Vector2* getVelocity();
  float getWidth();
  float getHeight();
  float getRadius();
  SDL_Texture* getTexture();

private:
  float radius;
};

#endif  //SRC_CIRCLE_H_
