#include "game_engine.h"
#include "gamestate.h"
#include "utils.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int SCREEN_FPS = 60;
const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;

GameEngine::GameEngine() {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    // Screen dimensions.
    width = SCREEN_WIDTH;
    height = SCREEN_HEIGHT;

    // Window and renderer.
    window = SDL_CreateWindow("Parallel collision detection.",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            width,
            height,
            SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    textFont = TTF_OpenFont("resources/fonts/Basica.ttf", 16);
    white = { 255, 255, 255, 255 };
    black = {0, 0, 0, 255};
    fps = 0;
    countedFrames = 0;
    exit = false;
}

void GameEngine::execute() {
  fpsTimer.start();
  while (!exit) {
    capTimer.start();

    fps = countedFrames / (fpsTimer.getTicks() / 1000.f);
    if (fps > 2000) {
      fps = 0;
    }
    input();
    update();
    render();
    ++countedFrames;
  }
  clean_up();
}

void GameEngine::clean_up() {
    // Clean up the current state.
    while (!states.empty()) {
        states.back()->clean_up(this);
        states.pop_back();
    }

    TTF_CloseFont(textFont);
    TTF_Quit();
    SDL_Quit();
}

void GameEngine::change_state(GameState* state) {
    // Clean up the current state.
    if (!states.empty()) {
        states.back()->clean_up(this);
        states.pop_back();
    }

    // Store and initialize the new state.
    states.push_back(state);
    states.back()->init(this);
}

void GameEngine::push_state(GameState* state) {
    // Pause current state.
    if ( !states.empty() )
        states.back()->pause();

    // Store and initialize the new state.
    states.push_back(state);
    states.back()->init(this);
}

void GameEngine::pop_state() {
    // Clean up the current state.
    if ( !states.empty() ) {
        states.back()->clean_up(this);
        states.pop_back();
    }

    // Resume previous state.
    if ( !states.empty() )
        states.back()->resume();
}

void GameEngine::input() {
    // Let the state handle events.
    states.back()->input(this);
}

void GameEngine::update() {
    // Let the state update the game.
    states.back()->update(this);
}

void GameEngine::render() {
    // Let the state draw the screen.
    states.back()->render(this);
}
