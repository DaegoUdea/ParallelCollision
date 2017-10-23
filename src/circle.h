#ifndef SRC_CIRCLE_H_
#define SRC_CIRCLE_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


class Circle {
 public:
    Circle();

    void move();
    void init();
    void setPosition(int new_x, int new_y);
    void setVelocity(int new_vx, int new_vy);
    void setRadius(int radius);
    void setTexture(SDL_Texture* tex);
    int getRadius();
    int getX();
    int getY();
    SDL_Texture* getTexture();

    // Texture
    SDL_Texture* texCircle;

    // positions.
    int x;
    int y;

    // Dimensions.
    int width;
    int height;
    int r;

    // old positions.
    int old_x;
    int old_y;

    // Velocity
    int vx;
    int vy;

    bool isMoving;
};

#endif  SRC_CIRCLE_H_
