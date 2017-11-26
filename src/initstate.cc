#include "initstate.h"
#include "utils.h"
#include <sstream>
#include <iostream>
#include <string>
#include "keyboard.h"
#include <omp.h>

InitState InitState::m_initstate;
void InitState::init(GameEngine* game) {
  exit = false;
  int width;
  int height;

  circle_texture = load_texture("resources/img/dot.bmp", game->renderer);
  SDL_QueryTexture(circle_texture, nullptr, nullptr, &width, &height);

  physics_manager = new PhysicsManager();

  leftBorder = new Rectangle(0 - 175.f, 0, 200.f, 600.f);
  rightBorder = new Rectangle(800.f - 25.f, 0, 200.f, 600.f);

  topBorder = new Rectangle(25.f, 0, 800.f-50.f, 25.f);
  bottomBorder = new Rectangle(25.f, 600.f-25.f, 800.f-50.f, 25.f);

  player = new Circle(50.f, 50.f, (float)width / 2);
  player->setTexture(circle_texture);

  velocity = 300;
  v_step = 5;

  for (int i = 0; i < 15; i++) {
    newCircle = new Circle(50.f, 100.f + (i*25), (float)width / 2);
    newCircle->setTexture(circle_texture);
    newCircle->setVelocity(new Vector2(250 * i, 0));
    circleObstacles.push_back(newCircle);
    physics_manager->addDynamicGameObject(newCircle);
  }

  physics_manager->addDynamicGameObject(player);
  physics_manager->addStaticGameObject(leftBorder);
  physics_manager->addStaticGameObject(rightBorder);
  physics_manager->addStaticGameObject(topBorder);
  physics_manager->addStaticGameObject(bottomBorder);
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
  Keyboard* keyboard = Keyboard::getInstance();

  while (SDL_PollEvent(&event)) {
    // Clicking 'x' or pressing F4.
    if (event.type == SDL_QUIT)
    exit = true;

    // Key is pressed.
    if (event.type == SDL_KEYDOWN) {
      switch (event.key.keysym.sym) {
        case SDLK_a:
        keyboard->setPressedKey("A");
        break;

        case SDLK_d:
        keyboard->setPressedKey("D");
        break;

        case SDLK_w:
        keyboard->setPressedKey("W");
        break;

        case SDLK_s:
        keyboard->setPressedKey("S");
        break;
      }
    }
    // Key is released.
    if (event.type == SDL_KEYUP) {
      switch (event.key.keysym.sym) {
        case SDLK_a:
        keyboard->setReleasedKey("A");
        break;

        case SDLK_d:
        keyboard->setReleasedKey("D");
        break;

        case SDLK_w:
        keyboard->setReleasedKey("W");
        break;

        case SDLK_s:
        keyboard->setReleasedKey("S");
        break;
      }
    }
  }
}

void InitState::update(GameEngine* game, float deltaTime) {

  if (exit) {game->quit();}

  Keyboard* keyboard = Keyboard::getInstance();

  Vector2* vel = player->getVelocity();

  if (keyboard->getPressedKey("A")) {
    vel->setX(-velocity);
  }
  else if (keyboard->getPressedKey("D")) {
    vel->setX(velocity);
  }
  else {
    vel->setX(0.f);
  }

  if (keyboard->getPressedKey("W")) {
    vel->setY(-velocity);
  }
  else if (keyboard->getPressedKey("S")) {
    vel->setY(velocity);
  }
  else {
    vel->setY(0.f);
  }

  physics_manager->handle_movement(game->deltaTime);
  // physics_manager->handle_collissions();
}

void InitState::render(GameEngine* game) {
  // Clear screen.
  SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 1);
  SDL_RenderClear(game->renderer);
  std::stringstream fps;
  fps << "FPS: " << game->fps << "  \nVelocity: " << velocity;

  draw_rectangle(game->renderer, leftBorder->getSDLRectangle(), 0xFF, 0x00, 0x00, 0xFF);
  draw_rectangle(game->renderer, rightBorder->getSDLRectangle(), 0x00, 0xFF, 0x00, 0xFF);
  draw_rectangle(game->renderer, topBorder->getSDLRectangle(), 0x00, 0x00, 0xFF, 0xFF);
  draw_rectangle(game->renderer, bottomBorder->getSDLRectangle(), 0xFF, 0xFF, 0x00, 0xFF);

  int size = circleObstacles.size();
  Circle* circle;

  for (int i = 0; i < size; i++) {
    circle = (Circle*) circleObstacles.at(i);
    render_texture(
      circle->getTexture(),
      game->renderer,
      (int)circle->getPosition()->getX(),
      (int)circle->getPosition()->getY(),
      nullptr);
    }

    render_texture(
      player->getTexture(),
      game->renderer,
      (int)player->getPosition()->getX(),
      (int)player->getPosition()->getY(),
      nullptr);

      game->fpsTexture = render_text(fps.str(), game->white, game->textFont, game->renderer);
      render_texture(game->fpsTexture, game->renderer, 0, 0);

      // Swap buffers.
      SDL_RenderPresent(game->renderer);
      SDL_DestroyTexture(game->fpsTexture);
    }
