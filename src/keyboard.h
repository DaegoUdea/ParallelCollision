#ifndef SRC_KEYBOARD_H_
#define SRC_KEYBOARD_H_

#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <map>
#include <stdlib.h>

class Keyboard {

public:
  static Keyboard* getInstance();

  bool getPressedKey(const char* key);
  bool getReleasedKey(const char* key);

  void setPressedKey(const char* key);
  void setReleasedKey(const char* key);
protected:
  Keyboard();
  ~Keyboard();

private:
  static Keyboard* _instance;
  std::map<const char*, bool > keyboard;
};

#endif  // SRC_KEYBOARD_H_
