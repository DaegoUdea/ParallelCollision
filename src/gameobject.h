#ifndef SRC_GAMEOBJECT_H_
#define SRC_GAMEOBJECT_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "vector2.h"

class GameObject {
 public:
    virtual void init() = 0;
    virtual void move() = 0;
    virtual void setDimension(float width, float height) = 0;
    virtual void onCollision(GameObject* object) = 0;

    // Setters
    virtual void setPosition(Vector2* position) = 0;
    virtual void setOldPosition(Vector2* oldPosition) = 0;
    virtual void refreshPosition() = 0;
    virtual void setWidth(float width) = 0;
    virtual void setHeight(float height) = 0;
    virtual void setVelocity(Vector2* velocity) = 0;
    virtual void setTexture(SDL_Texture* texture) = 0;

    // Getters
    virtual Vector2* getPosition() = 0;
    virtual Vector2* getOldPosition() = 0;
    virtual Vector2* getVelocity() = 0;
    virtual float getWidth() = 0;
    virtual float getHeight() = 0;
    virtual SDL_Texture* getTexture() = 0;

 protected:
    GameObject() {}
    ~GameObject() {
      delete[] position;
      delete[] velocity;
    }

    SDL_Texture* texture;

    Vector2* oldPosition;
    Vector2* position;
    Vector2* velocity;

    float width;
    float height;
};

#endif // SRC_GAMEOBJECT_H_
