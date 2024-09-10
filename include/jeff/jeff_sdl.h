#if !defined(JEFF_SDL_H)
#define JEFF_SDL_H 1

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include <SDL2/SDL.h>

SDL_Window *default_win(void);
SDL_Renderer *default_renderer(SDL_Window *, const Uint32);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* !JEFF_SDL_H */

/// vim:ts=4:sts=4:sw=4:et:ai:si:sta:noci:nopi:
