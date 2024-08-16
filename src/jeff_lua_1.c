#include <sys/types.h>
#include <stdio.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <jeff/jeff.h>
#include <jeff/jmemory.h>
#include <jeff/jstring.h>
#include <jeff/jeff_lua.h>

typedef struct _triggers {
  jbool with_libs;
} triggers_t;

lua_State *init_lua(const jbool with_libs) {
  lua_State *L = luaL_newstate();

  if (with_libs) {
    printf("%s\n", "Loading with libs");
    luaL_openlibs(L);
  }

  return L;
}

triggers_t *parse_argv(const uint argc, char **argv) {
  triggers_t *triggers = MALLOC(triggers_t);
  triggers->with_libs = JFALSE;

  if (argc == 1) {
    return triggers;
  }

  for (uint i = 0; i < argc - 1; i++) {
    triggers->with_libs = compare_two_strings("-v", argv[i]);
    if (triggers->with_libs) {
      break;
    }
  }

  return triggers;
}

int main(int argc, char **argv) {
  triggers_t *triggers = parse_argv((uint)argc, argv);
  lua_State *L = init_lua(triggers->with_libs);

  lua_close(L);
  return 0;
}
