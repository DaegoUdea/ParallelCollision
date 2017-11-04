#ifndef SRC_GAME_ENGINE_H_
#define SRC_GAME_ENGINE_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <string>
#include <sstream>
#include "gametimer.h"

class GameState;

class GameEngine {
 public:
    GameEngine();

    void clean_up();

    void change_state(GameState* state);
    void push_state(GameState* state);
    void pop_state();

    void execute();
    void input();
    void update(float deltaTime);
    void render();

    bool running() { return !exit; }
    void quit() { exit = true; }

    // Screen dimensions.
    int width;
    int height;

    // Window and renderer.
    SDL_Window* window;
    SDL_Renderer* renderer;

    // Timers
    GameTimer fpsTimer;
    GameTimer capTimer;

    // Fonts
    TTF_Font* textFont;

    // Colors
    SDL_Color white;
    SDL_Color black;

    // Textures
    SDL_Texture* fpsTexture;

    int countedFrames;
    float fps;
    std::stringstream fpsText;


 private:
    std::vector<GameState*> states;
    bool exit;
};

#endif  // SRC_GAME_ENGINE_H_
