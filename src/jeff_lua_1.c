#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <jeff/jeff.h>
#include <jeff/jeff_lua.h>

lua_State *init_lua(const jbool with_libs) {
  lua_State *L = luaL_newstate();

  if (with_libs) {
    luaL_openlibs(L);
  }

  return L;
}

int main(void) {
  lua_State *L = init_lua(1);

  lua_close(L);
  return 0;
}
