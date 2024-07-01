#include <jeff/jeff_lua.h>
#include <jeff/jeff.h>

lua_State *init_lua(const bool with_libs) {
  lua_State *L = luaL_newstate();

  if (with_libs) {
    luaL_openlibs(L);
  }

  return L;
}

int main(int argc, char **argv) {
  lua_State *L = init_lua(true);

  lua_close(L);
  return 0;
}
