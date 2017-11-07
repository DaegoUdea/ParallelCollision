#ifndef SRC_UTILS_H_
#define SRC_UTILS_H_

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>


void render_texture(
  SDL_Texture *tex,
  SDL_Renderer *ren,
  SDL_Rect dst,
  SDL_Rect *clip = nullptr);

void render_texture(
  SDL_Texture *tex,
  SDL_Renderer *ren,
  int x,
  int y,
  SDL_Rect *clip = nullptr);

void draw_rectangle(
  SDL_Renderer *ren,
  SDL_Rect* rectangle,
  Uint8 r,
  Uint8 g,
  Uint8 b,
  Uint8 a);

SDL_Texture* render_text(
  const std::string &message,
  SDL_Color color,
  TTF_Font* font,
  SDL_Renderer *renderer);

SDL_Texture* load_texture(
  const std::string &file,
  SDL_Renderer *ren);


#endif  // SRC_UTILS_H_
