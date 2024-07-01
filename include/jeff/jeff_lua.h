#ifndef JEFF_LUA_H
#define JEFF_LUA_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <stdbool.h>

static lua_State *init_lua(const bool);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !JEFF_LUA_H
