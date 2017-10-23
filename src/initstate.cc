#include "initstate.h"
#include "utils.h"
#include <sstream>
#include <iostream>
#include <string>

InitState InitState::m_initstate;
void InitState::init(GameEngine* game) {
  exit = false;
  player.setTexture(load_texture("resources/img/dot.bmp", game->renderer));
  player.setPosition(50, 50);
  player.setRadius(30);
}

void InitState::clean_up(GameEngine* game) {
  IMG_Quit();
}

void InitState::pause() {}

void InitState::resume() {}

void InitState::reset() {}

void InitState::input(GameEngine* game) {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    // Clicking 'x' or pressing F4.
    if (event.type == SDL_QUIT)
    exit = true;

    // Key is pressed.
    if (event.type == SDL_KEYDOWN) {

      switch (event.key.keysym.sym) {
        case SDLK_ESCAPE:
        exit = true;
        break;

        case SDLK_a: case SDLK_LEFT:
        player.setVelocity(-1, 0);
        break;

        case SDLK_d: case SDLK_RIGHT:
        player.setVelocity(1, 0);
        break;

        case SDLK_w: case SDLK_UP:
        player.setVelocity(0, -1);
        break;

        case SDLK_s: case SDLK_DOWN:
        player.setVelocity(0, 1);
        break;

        case SDLK_SPACE:
        break;

        default:
        break;
      }
    }
    if (event.type == SDL_KEYUP) {
      player.setVelocity(0, 0);
    }
  }
}

void InitState::update(GameEngine* game) {
  if (exit) {
    game->quit();
  }
  player.move();
}

void InitState::render(GameEngine* game) {
  // Clear screen.
  SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 1);
  SDL_RenderClear(game->renderer);
  printf("FPS: %d\n", game->fps);

  render_texture(player.getTexture(), game->renderer,player.getX(), player.getY(), nullptr);

  // game->fpsTexture = render_text(fps, game->white, game->textFont, game->renderer);
  // render_texture(game->fpsTexture, game->renderer, 0, 0);

  // Swap buffers.
  SDL_RenderPresent(game->renderer);
}
