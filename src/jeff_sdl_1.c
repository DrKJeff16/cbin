#include <SDL2/SDL.h>         // for SDL_Quit, SDL_INIT_EVERYTHING
#include <SDL2/SDL_image.h>   // for IMG_Load
#include <SDL2/SDL_render.h>  // for SDL_CreateRenderer, SDL_CreateTextureFr...
#include <SDL2/SDL_stdinc.h>  // for Uint32
#include <SDL2/SDL_timer.h>   // for SDL_Delay
#include <SDL2/SDL_video.h>   // for SDL_Window, SDL_CreateWindow, SDL_Destr...
#include <jeff/jeff.h>        // for err, JEFF_H
#include <jeff/jeff_sdl.h>    // for default_renderer, default_win
#include <stddef.h>           // for NULL
#include "SDL_error.h"        // for SDL_GetError
#include "SDL_events.h"       // for SDL_PollEvent, SDL_Event, SDL_KEYDOWN
#include "SDL_rect.h"         // for SDL_Rect
#include "SDL_scancode.h"     // for SDL_SCANCODE_A, SDL_SCANCODE_COMMA, SDL...
#include "SDL_surface.h"      // for SDL_FreeSurface, SDL_Surface

SDL_Window *default_win(void) {
  return SDL_CreateWindow("GAME", SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED, 1000, 1000, 0);
}

SDL_Renderer *default_renderer(SDL_Window *win, const Uint32 flags) {
  return SDL_CreateRenderer(win, -1, flags);
}

int main(void) {
  SDL_Window *win = default_win();

  if (SDL_INIT_EVERYTHING) {
#ifdef JEFF_H
    err("error initializing SDL: %s\n", SDL_GetError());
#else
    fprintf(stderr, "error initializing SDL: %s\n", SDL_GetError());
#endif /* JEFF_H */
  }

  Uint32 render_flags = SDL_RENDERER_ACCELERATED;

  SDL_Renderer *rend = default_renderer(win, render_flags);

  SDL_Surface *surface;
  surface = IMG_Load("assets/face.png");

  SDL_Texture *texture = SDL_CreateTextureFromSurface(rend, surface);

  SDL_FreeSurface(surface);

  SDL_Rect dest;

  SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

  dest.w /= 6;
  dest.h /= 6;
  dest.x = (1000 - dest.w) / 2;
  dest.y = (1000 - dest.h) / 2;

  int close = 0, speed = 350;
  int change = speed / 30;

  while (!close) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
        case SDL_SCANCODE_ESCAPE:
          close = 1;
          break;
        case SDL_KEYDOWN:
          switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_COMMA:
            case SDL_SCANCODE_W:
            case SDL_SCANCODE_UP:
              dest.y -= change;
              break;
            case SDL_SCANCODE_A:
            case SDL_SCANCODE_LEFT:
              dest.x -= change;
              break;
            case SDL_SCANCODE_S:
            case SDL_SCANCODE_O:
            case SDL_SCANCODE_DOWN:
              dest.y += change;
              break;
            case SDL_SCANCODE_D:
            case SDL_SCANCODE_E:
            case SDL_SCANCODE_RIGHT:
              dest.x += change;
              break;
            default:
              break;
          }
      }
    }

    if (dest.x + dest.w > 1000) {
      dest.x = 1000 - dest.w;
    }

    if (dest.x < 0) {
      dest.x = 0;
    }

    if (dest.y + dest.h > 1000) {
      dest.y = 1000 - dest.h;
    }

    if (dest.y < 0) {
      dest.y = 0;
    }

    SDL_RenderClear(rend);
    SDL_RenderCopy(rend, texture, NULL, &dest);

    SDL_RenderPresent(rend);

    SDL_Delay(1000 / 60);
  }

  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(rend);
  SDL_DestroyWindow(win);

  SDL_Quit();

  return 0;
}
