#ifndef SRC_INISTATE_H_
#define SRC_INISTATE_H_

#include "gamestate.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "circle.h"


class InitState : public GameState {
 public:
    void init(GameEngine* game);
    void clean_up(GameEngine* game);

    void pause();
    void resume();
    void reset();

    void input(GameEngine* game);
    void update(GameEngine* game);
    void render(GameEngine* game);

    static InitState* Instance() { return &m_initstate; }

 protected:
    InitState() { }

 private:
    static InitState m_initstate;
    Circle player;

    bool exit;
};


#endif  // SRC_INISTATE_H_
