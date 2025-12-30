#include <jeff/jeff.h>
#include <jeff/jluajit.h>
#include <lua.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

lua_State *new_lua_state(void) {
  lua_State *L = luaL_newstate();
  luaL_openlibs(L);

  return L;
}

void jlua_push(lua_State *L, const jlua_type type, void *item, ...) {
  if (null_ptr(item)) {
    lua_pushnil(L);
    return;
  }

  switch (type) {
    case JLUA_NIL:
      lua_pushnil(L);
      break;

    case JLUA_BOOL:
      lua_pushboolean(L, *(int *)item);
      break;

    case JLUA_NUM:
      lua_pushnumber(L, *(lua_Number *)item);
      break;

    case JLUA_LSTR:
      lua_pushlstring(L, (char *)item, strlen((char *)item) + 1);
      break;

    case JLUA_STR:
      lua_pushstring(L, (char *)item);
      break;
  }
}

void jlua_die(const int code, lua_State *L, char *const fmt, ...) {
  if (!null_ptr(fmt)) {
    va_list argp;
    va_start(argp, fmt);
    vfprintf((!code) ? stderr : stdout, fmt, argp);
    va_end(argp);
  }

  lua_close(L);
  die(code, NULL);
}

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
