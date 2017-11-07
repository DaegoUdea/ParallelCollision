#include "initstate.h"
#include "utils.h"
#include <sstream>
#include <iostream>
#include <string>
#include "keyboard.h"

InitState InitState::m_initstate;
void InitState::init(GameEngine* game) {
  exit = false;
  int width;
  int height;

  circle_texture = load_texture("resources/img/dot.bmp", game->renderer);
  SDL_QueryTexture(circle_texture, nullptr, nullptr, &width, &height);

  collision_manager = new CollisionManager();

  leftBorder = new Rectangle(0 - 175.f, 0, 200.f, 600.f);
  rightBorder = new Rectangle(800.f - 25.f, 0, 200.f, 600.f);

  topBorder = new Rectangle(25.f, 0, 800.f-50.f, 25.f);
  bottomBorder = new Rectangle(25.f, 600.f-25.f, 800.f-50.f, 25.f);

  player = new Circle(50.f, 50.f, (float)width);
  circle_obstacle1 = new Circle(50.f, 100.f, (float)width);
  circle_obstacle2 = new Circle(50.f, 200.f, (float)width);
  circle_obstacle3 = new Circle(50.f, 300.f, (float)width);
  circle_obstacle4 = new Circle(50.f, 400.f, (float)width);

  player->setTexture(circle_texture);
  circle_obstacle1->setTexture(circle_texture);
  circle_obstacle2->setTexture(circle_texture);
  circle_obstacle3->setTexture(circle_texture);
  circle_obstacle4->setTexture(circle_texture);

  circle_obstacle1->setVelocity(new Vector2(500, 0));
  circle_obstacle2->setVelocity(new Vector2(1500, 0));
  circle_obstacle3->setVelocity(new Vector2(2500, 0));
  circle_obstacle4->setVelocity(new Vector2(3500, 0));

  velocity = 300;
  v_step = 5;

  collision_manager->addGameObject(player);
  collision_manager->addGameObject(circle_obstacle1);
  collision_manager->addGameObject(circle_obstacle2);
  collision_manager->addGameObject(circle_obstacle3);
  collision_manager->addGameObject(circle_obstacle4);
  collision_manager->addGameObject(leftBorder);
  collision_manager->addGameObject(rightBorder);
  collision_manager->addGameObject(topBorder);
  collision_manager->addGameObject(bottomBorder);
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
  // printf("Time %f\n", deltaTime / 1000.f);
  if (exit) {
    game->quit();
  }

  Keyboard* keyboard = Keyboard::getInstance();

  float x = player->getPosition()->getX();
  float y = player->getPosition()->getY();

  if (keyboard->getPressedKey("A")) {
    x += -velocity;
  }

  if (keyboard->getPressedKey("D")) {
    x += velocity;
  }

  if (keyboard->getPressedKey("W")) {
    y += -velocity;
  }

  if (keyboard->getPressedKey("S")) {
    y += velocity;
  }

  player->setPosition(Vector2::lerp(player->getPosition(), new Vector2(x, y), game->deltaTime));
  circle_obstacle1->move(game->deltaTime);
  circle_obstacle2->move(game->deltaTime);
  circle_obstacle3->move(game->deltaTime);
  circle_obstacle4->move(game->deltaTime);
  collision_manager->handle_collissions();
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

  render_texture(
    player->getTexture(),
    game->renderer,
    (int)player->getPosition()->getX(),
    (int)player->getPosition()->getY(),
    nullptr);

  render_texture(
    circle_obstacle1->getTexture(),
    game->renderer,
    (int)circle_obstacle1->getPosition()->getX(),
    (int)circle_obstacle1->getPosition()->getY(),
    nullptr);

  render_texture(
    circle_obstacle2->getTexture(),
    game->renderer,
    (int)circle_obstacle2->getPosition()->getX(),
    (int)circle_obstacle2->getPosition()->getY(),
    nullptr);

  render_texture(
    circle_obstacle3->getTexture(),
    game->renderer,
    (int)circle_obstacle3->getPosition()->getX(),
    (int)circle_obstacle3->getPosition()->getY(),
    nullptr);

  render_texture(
    circle_obstacle4->getTexture(),
    game->renderer,
    (int)circle_obstacle4->getPosition()->getX(),
    (int)circle_obstacle4->getPosition()->getY(),
    nullptr);

  game->fpsTexture = render_text(fps.str(), game->white, game->textFont, game->renderer);
  render_texture(game->fpsTexture, game->renderer, 0, 0);

  // Swap buffers.
  SDL_RenderPresent(game->renderer);
}
