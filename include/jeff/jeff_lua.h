#ifndef JEFF_LUA_H
#define JEFF_LUA_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <sys/types.h>
#include <lua.h>

typedef struct _p_flags {
  jbool VERBOSE;
  jbool LIBS;
} p_flags;

static p_flags *PROGRAM_FLAGS;

lua_State *init_lua();
void lua_err(lua_State *L, const char *fmt, ...);
void parse_argv(const uint argc, char **argv);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !JEFF_LUA_H */
