#include <jeff/jluajit.h>

lua_State *new_lua_state(void) {
  lua_State *L = luaL_newstate();
  luaL_openlibs(L);

  return L;
}

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
