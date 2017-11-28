#include "initstate.h"
#include "utils.h"
#include <sstream>
#include <iostream>
#include <string>
#include "keyboard.h"
#include <omp.h>
#include "game_properties.h"

InitState InitState::m_initstate;
void InitState::init(GameEngine* game) {
  exit = false;
  int width;
  int height;

  circle_texture = load_texture("resources/img/dot.bmp", game->renderer);
  SDL_QueryTexture(circle_texture, nullptr, nullptr, &width, &height);

  physics_manager = new PhysicsManager();

  leftBorder = new Rectangle(0 - 200.f, 0, 200.f, 600.f);
  rightBorder = new Rectangle(1200.f, 0, 200.f, 600.f);

  topBorder = new Rectangle(0, -975.f, 1200, 1000.f);
  bottomBorder = new Rectangle(0, 600.f, 1200, 1000.f);

  player = new Circle(5.f, 300.f, (float)width / 2);
  player->setTexture(circle_texture);

  velocity = 300;
  v_step = 5;

  for (int i = 0; i < 160; i++) {
    newCircle = new Circle(120.f + (i * 6 ), 30.f, (float)width / 2);
    newCircle->setTexture(circle_texture);
    newCircle->setVelocity(new Vector2(0, 500 + (i * 10 * 0)));
    circleObstacles.push_back(newCircle);
    physics_manager->addDynamicGameObject(newCircle);

    newCircle = new Circle(120.f + (i * 6 ), 550.f, (float)width / 2);
    newCircle->setTexture(circle_texture);
    newCircle->setVelocity(new Vector2(0, -500 + (i * 10 * 0)));
    circleObstacles.push_back(newCircle);
    physics_manager->addDynamicGameObject(newCircle);

    newCircle = new Circle(120.f + (i * 6 ), 200.f, (float)width / 2);
    newCircle->setTexture(circle_texture);
    newCircle->setVelocity(new Vector2(0, -500 + (i * 10 * 0)));
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
  GameProperties* properties = GameProperties::getInstance();

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

        case SDLK_c:
        properties->is_collision_on = !properties->is_collision_on;
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

  if (keyboard->getPressedKey("A")) {vel->setX(-velocity);}
  else if (keyboard->getPressedKey("D")) {vel->setX(velocity);}
  else {vel->setX(0.f);}

  if (keyboard->getPressedKey("W")) {vel->setY(-velocity);}
  else if (keyboard->getPressedKey("S")) {vel->setY(velocity);}
  else {vel->setY(0.f);}

  physics_manager->handle_movement();
  physics_manager->handle_collissions();
}

void InitState::render(GameEngine* game) {
  GameProperties* properties = GameProperties::getInstance();
  // Clear screen.
  SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 1);
  SDL_RenderClear(game->renderer);

  draw_rectangle(game->renderer, leftBorder->getSDLRectangle(), 0xFF, 0x00, 0x00, 0xFF);
  draw_rectangle(game->renderer, rightBorder->getSDLRectangle(), 0x00, 0xFF, 0x00, 0xFF);
  draw_rectangle(game->renderer, topBorder->getSDLRectangle(), 0x00, 0x00, 0x00, 0xFF);
  draw_rectangle(game->renderer, bottomBorder->getSDLRectangle(), 0xFF, 0xFF, 0x00, 0xFF);

  int size = circleObstacles.size();
  Circle* circle;
  int i = 0;
  SDL_Renderer* renderer= game->renderer;

  for (i = 0; i < size; i++) {
    circle = (Circle*) circleObstacles.at(i);
    render_texture(
      circle->getTexture(),
      renderer,
      (int)circle->getPosition()->getX(),
      (int)circle->getPosition()->getY(),
      nullptr
    );
  }

  render_texture(
    player->getTexture(),
    game->renderer,
    (int)player->getPosition()->getX(),
    (int)player->getPosition()->getY(),
    nullptr
  );

  std::stringstream fps;
  fps << "FPS: " << properties->fps;
  game->fpsTexture = render_text(fps.str(), game->white, game->textFont, game->renderer);
  render_texture(game->fpsTexture, game->renderer, 0, 0);

  // Swap buffers.
  SDL_RenderPresent(game->renderer);
  SDL_DestroyTexture(game->fpsTexture);
}
