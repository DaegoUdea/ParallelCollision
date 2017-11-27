#include "game_properties.h"

GameProperties* GameProperties::_instance = 0;

GameProperties::GameProperties() {

}

GameProperties::~GameProperties() {

}

GameProperties* GameProperties::getInstance() {
  if (_instance == 0) {
    _instance = new GameProperties;
  }
  return _instance;
}
