#include <sys/types.h>     // for uint
#include <lauxlib.h>       // for luaL_newstate
#include <lua.h>           // for lua_State, lua_close
#include <lualib.h>        // for luaL_openlibs
#include <stdarg.h>        // for va_end, va_start
#include <stdio.h>         // for printf, vfprintf, NULL, stderr, va_list
#include <stdlib.h>        // for free, exit, EXIT_FAILURE
#include <string.h>        // for strcmp
#include <jeff/jeff.h>     // for _jbool, die, err
#include <jeff/jmemory.h>  // for MALLOC
#include <jeff/jlua.h>     // for p_flags, init_lua_state, k_flags, lua_err

static p_flags *PROGRAM_FLAGS = NULL;

const k_flags KEYWORD_FLAGS = {
  .VERBOSE = "-v",
  .LIBS = "-l",
};

static void stack_dump(lua_State *L) {
  int i = 1, top = lua_gettop(L);

  for (; i <= top; i++) { /* repeat for each level */
    int t = lua_type(L, i);
    switch (t) {
      case LUA_TSTRING: /* strings */
        printf("`%s'", lua_tostring(L, i));
        break;
      case LUA_TBOOLEAN: /* booleans */
        printf(lua_toboolean(L, i) ? "true" : "false");
        break;
      case LUA_TNUMBER: /* numbers */
        printf("%g", lua_tonumber(L, i));
        break;
      default: /* other values */
        printf("%s", lua_typename(L, t));
        break;
    }
    printf(" | "); /* put a separator */
  }
  printf("\n"); /* end the listing */
}

void lua_err(lua_State *L, char *const fmt, ...) {
  va_list argp;

  va_start(argp, fmt);
  vfprintf(stderr, fmt, argp);
  va_end(argp);

  lua_close(L);
  free(PROGRAM_FLAGS);

  exit(EXIT_FAILURE);
}

static void init_p_flags(void) {
  PROGRAM_FLAGS = MALLOC(p_flags);
  PROGRAM_FLAGS->VERBOSE = JFALSE;
  PROGRAM_FLAGS->LIBS = JFALSE;
}

lua_State *init_lua_state(void) {
  lua_State *L = luaL_newstate();

  if (PROGRAM_FLAGS->LIBS) {
    luaL_openlibs(L);

    if (PROGRAM_FLAGS->VERBOSE) {
      printf("%s\n", "Loading with libs");
    }
  }

  return L;
}

void parse_argv(const uint argc, char **argv) {
  if (!argc) {
    return;
  }

  for (uint i = 1; i <= argc; i++) {
    if (argv[i][0] != '-') {
      continue;
    } else {
      char *str = argv[i];

      if (!strcmp(KEYWORD_FLAGS.VERBOSE, str)) {
        PROGRAM_FLAGS->VERBOSE = JTRUE;
      } else if (!strcmp(KEYWORD_FLAGS.LIBS, str)) {
        PROGRAM_FLAGS->LIBS = JTRUE;
      } else {
        free(PROGRAM_FLAGS);
        verr("Invalid argument `%s`\n", str);
        die(127, NULL);
      }
    }
  }
}

int main(int argc, char **argv) {
  init_p_flags();

  argc--;
  parse_argv((uint)argc, argv);
  lua_State *L = init_lua_state();

  getchar();

  stack_dump(L);
  lua_pushboolean(L, JTRUE);
  lua_pushnumber(L, 10.);
  lua_pushnil(L);
  lua_pushstring(L, "hello");
  stack_dump(L);
  /* true  10  nil  `hello'  */

  lua_pushvalue(L, -4);
  stack_dump(L);
  /* true  10  nil  `hello'  true  */

  lua_replace(L, 3);
  stack_dump(L);
  /* true  10  true  `hello'  */

  lua_settop(L, 6);
  stack_dump(L);
  /* true  10  true  `hello'  nil  nil  */

  lua_remove(L, -3);
  stack_dump(L);
  /* true  10  true  nil  nil  */

  lua_settop(L, -5);
  stack_dump(L);
  /* true  */

  lua_close(L);
  return 0;
}

/// vim:ts=4:sts=4:sw=4:et:ai:si:sta:noci:nopi:
