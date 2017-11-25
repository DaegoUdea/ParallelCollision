#ifndef SRC_INISTATE_H_
#define SRC_INISTATE_H_

#include "gamestate.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "circle.h"
#include "rectangle.h"
#include "physics_manager.h"


class InitState : public GameState {
 public:
    void init(GameEngine* game);
    void clean_up(GameEngine* game);

    void pause();
    void resume();
    void reset();

    void input(GameEngine* game);
    void update(GameEngine* game, float deltaTime);
    void render(GameEngine* game);

    static InitState* Instance() { return &m_initstate; }

 protected:
    InitState() { }

 private:
    static InitState m_initstate;
    PhysicsManager* physics_manager;
    SDL_Texture* circle_texture;

    Circle* player;
    Circle* circle_obstacle1;
    Circle* circle_obstacle2;
    Circle* circle_obstacle3;
    Circle* circle_obstacle4;

    Rectangle* leftBorder;
    Rectangle* rightBorder;
    Rectangle* topBorder;
    Rectangle* bottomBorder;

    float velocity;
    float v_step;

    bool exit;
};

#endif  // SRC_INISTATE_H_
