#include "initstate.h"
#include "utils.h"
#include <sstream>
#include <iostream>
#include <string>
// #include "vector2.h"

InitState InitState::m_initstate;
void InitState::init(GameEngine* game) {
  exit = false;
  circle_texture = load_texture("resources/img/dot.bmp", game->renderer);

  player.setTexture(circle_texture);
  player.setPosition(new Vector2(50, 50));

  circle_obstacle1.setTexture(circle_texture);
  circle_obstacle1.setPosition(new Vector2(300, 50));

  circle_obstacle2.setTexture(circle_texture);
  circle_obstacle2.setPosition(new Vector2(50, 300));

}

void InitState::clean_up(GameEngine* game) {
  SDL_DestroyTexture(circle_texture);
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
        player.getVelocity()->setX(-300);
        break;

        case SDLK_d: case SDLK_RIGHT:
        player.getVelocity()->setX(300);
        break;

        case SDLK_w: case SDLK_UP:
        player.getVelocity()->setY(-300);
        break;

        case SDLK_s: case SDLK_DOWN:
        player.getVelocity()->setY(300);
        break;

        case SDLK_SPACE:
        player.getVelocity()->setX(0);
        player.getVelocity()->setY(0);
        break;

        default:
        break;
      }
    }
    if (event.type == SDL_KEYUP) {
      switch (event.key.keysym.sym) {
        case SDLK_ESCAPE:
        exit = true;
        break;

        case SDLK_a: case SDLK_LEFT:
        player.getVelocity()->setX(0);
        break;

        case SDLK_d: case SDLK_RIGHT:
        player.getVelocity()->setX(0);
        break;

        case SDLK_w: case SDLK_UP:
        player.getVelocity()->setY(0);
        break;

        case SDLK_s: case SDLK_DOWN:
        player.getVelocity()->setY(0);
        break;

        case SDLK_SPACE:
        player.getVelocity()->setX(0);
        player.getVelocity()->setY(0);
        break;

        default:
        break;
      }
    }
  }
}

void InitState::update(GameEngine* game, float deltaTime) {
  // printf("Time %f\n", deltaTime / 1000.f);
  if (exit) {
    game->quit();
  }
  player.move(deltaTime / 1000.f);
}

void InitState::render(GameEngine* game) {
  // Clear screen.
  SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 1);
  SDL_RenderClear(game->renderer);
  std::stringstream fps;
  fps << "FPS: " << game->fps;
  // std::cout << fps.str() + "\n";

  render_texture(
    player.getTexture(),
    game->renderer,
    (int)player.getPosition()->getX(),
    (int)player.getPosition()->getY(),
    nullptr);

  render_texture(
    circle_obstacle1.getTexture(),
    game->renderer,
    (int)circle_obstacle1.getPosition()->getX(),
    (int)circle_obstacle1.getPosition()->getY(),
    nullptr);

  render_texture(
    circle_obstacle2.getTexture(),
    game->renderer,
    (int)circle_obstacle2.getPosition()->getX(),
    (int)circle_obstacle2.getPosition()->getY(),
    nullptr);

  game->fpsTexture = render_text(fps.str(), game->black, game->textFont, game->renderer);
  render_texture(game->fpsTexture, game->renderer, 0, 0);

  // Swap buffers.
  SDL_RenderPresent(game->renderer);
}
