#ifndef SRC_RECTANGLE_H_
#define SRC_RECTANGLE_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "gameobject.h"
#include "vector2.h"

class Rectangle : public GameObject {
public:
  Rectangle(float x, float y, float width, float height);

  void init();
  void move(float deltaTime);
  void setDimension(float width, float height);
  SDL_Rect* getSDLRectangle();
  void onCollision(GameObject* object);

  // Setters
  void setPosition(Vector2* position);
  void refreshPosition();
  void setWidth(float width);
  void setHeight(float height);
  void setVelocity(Vector2* velocity);
  void setTexture(SDL_Texture* texture);

  // Getters
  Vector2* getPosition();
  Vector2* getVelocity();
  float getWidth();
  float getHeight();
  SDL_Texture* getTexture();

private:
  SDL_Rect sdl_rectangle;
};

#endif  // SRC_RECTANGLE_H_
