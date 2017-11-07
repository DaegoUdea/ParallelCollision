#include "keyboard.h"
#include <SDL2/SDL.h>
#include <stdlib.h>

Keyboard* Keyboard::_instance = 0;

Keyboard::Keyboard() {
}

Keyboard::~Keyboard() {

}

Keyboard* Keyboard::getInstance() {
  if (_instance == 0) {
    _instance = new Keyboard;
  }
  return _instance;
}

bool Keyboard::getPressedKey(const char* key) {
  return keyboard.find(key)->second == true;
}

bool Keyboard::getReleasedKey(const char* key) {
  return keyboard.find(key)->second == false;
}

void Keyboard::setPressedKey(const char* key) {
  keyboard[key] = true;
}

void Keyboard::setReleasedKey(const char* key) {
  keyboard[key] = false;
}
