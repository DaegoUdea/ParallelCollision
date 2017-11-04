#ifndef SRC_GAMEOBJECT_H_
#define SRC_GAMEOBJECT_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "vector2.h"

class GameObject {
 public:
    virtual void init() = 0;
    virtual void move(float deltaTime) = 0;
    virtual void setDimension(int width, int height) = 0;

    // Setters
    virtual void setPosition(Vector2* position) = 0;
    virtual void setWidth(int width) = 0;
    virtual void setHeight(int height) = 0;
    virtual void setVelocity(Vector2* velocity) = 0;
    virtual void setTexture(SDL_Texture* texture) = 0;

    // Getters
    virtual Vector2* getPosition() = 0;
    virtual Vector2* getVelocity() = 0;
    virtual int getWidth(int width) = 0;
    virtual int getHeight(int height) = 0;
    virtual SDL_Texture* getTexture() = 0;

 protected:
    GameObject() {}

  private:
    SDL_Texture* texture;

    Vector2* position;
    Vector2* velocity;

    int width;
    int height;
};

#endif // SRC_GAMEOBJECT_H_
