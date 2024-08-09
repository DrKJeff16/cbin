#ifndef JEFF_LUA_H
#define JEFF_LUA_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <sys/types.h>
#include <lua.h>

static lua_State *init_lua(const uint);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !JEFF_LUA_H */
