#ifndef SRC_CIRCLE_H_
#define SRC_CIRCLE_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "gameobject.h"
#include "vector2.h"

class Circle : public GameObject {
public:
  Circle();

  void init();
  void move(float deltaTime);
  void setDimension(int width, int height);

  // Setters
  void setPosition(Vector2* position);
  void setWidth(int width);
  void setHeight(int height);
  void setVelocity(Vector2* velocity);
  void setTexture(SDL_Texture* texture);

  // Getters
  Vector2* getPosition();
  Vector2* getVelocity();
  int getWidth(int width);
  int getHeight(int height);
  SDL_Texture* getTexture();

private:
  SDL_Texture* texture;

  Vector2* position;
  Vector2* velocity;

  int width;
  int height;
};

#endif  //SRC_CIRCLE_H_
