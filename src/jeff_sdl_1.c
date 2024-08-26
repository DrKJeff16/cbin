#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <stdlib.h>
#include <jeff/jeff.h>
#include <jeff/jmemory.h>
#include <jeff/jeff_sdl.h>

#ifndef _JASSET_PATH
#define _JASSET_PATH "~/.local/share/jassets/face.png"
#endif /* !_JASSET_PATH */

#define WIDTH 1920
#define HEIGHT 1080

typedef enum _point_flag {
  NOOP = 0,
  TOP,
  RIGHT,
  BOTTOM,
  LEFT,
} direction_flag;

typedef struct _sdl_env {
  SDL_Window *win;
  SDL_Renderer *rend;
  SDL_Surface *surface;
  SDL_Texture *texture;
  SDL_Rect *dest;
  direction_flag *dflag;
  jbool *rect_created;
} SDL_Env;

SDL_Window *default_win(void) {
  return SDL_CreateWindow("TEST", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
}

SDL_Renderer *default_renderer(SDL_Window *win, const Uint32 flags) {
  return SDL_CreateRenderer(win, -1, flags);
}

void sdl_kill(SDL_Window *win, SDL_Renderer *rend, SDL_Surface *surface, SDL_Texture *texture,
              SDL_Rect *dest, direction_flag *dflag, jbool *rect_created) {
  free(rect_created);
  free(dflag);
  free(dest);
  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(rend);
  SDL_DestroyWindow(win);
}

SDL_Env *sdl_env_init(void) {
  SDL_Env *env = MALLOC(SDL_Env);
  env->win = default_win();
  env->rend = NULL;
  env->surface = NULL;
  env->texture = NULL;
  env->dest = MALLOC(SDL_Rect);
  env->dflag = MALLOC(direction_flag);
  env->rect_created = MALLOC(jbool);
  *(env->rect_created) = JFALSE;

  if (!SDL_INIT_EVERYTHING) {
    verr("error initializing SDL: %s\n", SDL_GetError());
  }

  return env;
}

void sdl_env_kill(SDL_Env *env) {
  free(env->rect_created);
  free(env->dflag);
  free(env->dest);
  SDL_DestroyTexture(env->texture);
  SDL_DestroyRenderer(env->rend);
  SDL_DestroyWindow(env->win);

  free(env);
}

void reset_cursor(SDL_Rect *dest, direction_flag *dflag) {
  if (!dflag || dflag == NULL) {
    dflag = MALLOC(direction_flag);
    *dflag = NOOP;
  }
  if (!dest || dest == NULL) {
    dest = MALLOC(SDL_Rect);
    return;
  }

  if (dest->x + dest->w > WIDTH) {
    dest->x = WIDTH - dest->w;

    if (*dflag != RIGHT) {
      *dflag = RIGHT;
      printf("Reached right\n");
    }
  }
  if (dest->x < 0) {
    dest->x = 0;

    if (*dflag != LEFT) {
      *dflag = LEFT;
      printf("Reached left\n");
    }
  }
  if (dest->y + dest->h > HEIGHT) {
    dest->y = HEIGHT - dest->h;

    if (*dflag != BOTTOM) {
      *dflag = BOTTOM;
      printf("Reached bottom\n");
    }
  }
  if (dest->y < 0) {
    dest->y = 0;

    if (*dflag != TOP) {
      *dflag = TOP;
      printf("Reached top\n");
    }
  }
}

void init_cursor(SDL_Rect *dest, direction_flag *dflag, jbool *rect_created) {
  if (!dest || dest == NULL) {
    dest = MALLOC(SDL_Rect);
  }
  if (!dflag || dflag == NULL) {
    dflag = MALLOC(direction_flag);
  }
  if (!rect_created || rect_created == NULL) {
    rect_created = MALLOC(jbool);
    *rect_created = JFALSE;
  }

  *dflag = NOOP;

  if (!(*rect_created)) {
    dest->w /= 6;
    dest->h /= 6;
    *rect_created = JTRUE;
  }

  dest->x = (int)((WIDTH - dest->w) / 2);
  dest->y = (int)((HEIGHT - dest->h) / 2);
}

int main(void) {
  SDL_Env *env = sdl_env_init();

  Uint32 render_flags = SDL_RENDERER_ACCELERATED;
  const Uint32 delay = (Uint32)(1000 / 40);

  env->rend = default_renderer(env->win, render_flags);
  env->surface = IMG_Load(_JASSET_PATH);
  env->texture = SDL_CreateTextureFromSurface(env->rend, env->surface);

  SDL_FreeSurface(env->surface);
  SDL_QueryTexture(env->texture, NULL, NULL, &(env->dest->w), &(env->dest->h));

  init_cursor(env->dest, env->dflag, env->rect_created);

  int close = 0;
  int speed = 400;
  int change = speed / 30;

  while (!close) {
    SDL_Event *event = MALLOC(SDL_Event);

    while (SDL_PollEvent(event)) {
      switch (event->type) {
        case SDL_KEYDOWN:
          switch (event->key.keysym.scancode) {
            case SDL_SCANCODE_ESCAPE:
            case SDL_SCANCODE_DELETE:
              close = 1;
              break;
            case SDL_SCANCODE_RETURN:
              init_cursor(env->dest, env->dflag, env->rect_created);
              break;
            case SDL_SCANCODE_COMMA:
            case SDL_SCANCODE_K:
            case SDL_SCANCODE_W:
            case SDL_SCANCODE_UP:
              env->dest->y -= change;
              break;
            case SDL_SCANCODE_A:
            case SDL_SCANCODE_H:
            case SDL_SCANCODE_LEFT:
              env->dest->x -= change;
              break;
            case SDL_SCANCODE_L:
            case SDL_SCANCODE_O:
            case SDL_SCANCODE_S:
            case SDL_SCANCODE_DOWN:
              env->dest->y += change;
              break;
            case SDL_SCANCODE_D:
            case SDL_SCANCODE_E:
            case SDL_SCANCODE_J:
            case SDL_SCANCODE_RIGHT:
              env->dest->x += change;
              break;
            default:
              break;
          }
          break;
        default:
          break;
      }
    }

    reset_cursor(env->dest, env->dflag);
    SDL_RenderClear(env->rend);
    SDL_RenderCopy(env->rend, env->texture, NULL, env->dest);
    SDL_RenderPresent(env->rend);

    free(event);

    SDL_Delay(delay);
  }

  /* sdl_kill(env->win, env->rend, env->surface, env->texture, env->dest, env->dflag,
   * env->rect_created); */
  sdl_env_kill(env);

  return 0;
}

/// vim:ts=2:sts=2:sw=2:et:ai:si:sta:noci:nopi:
