#include <jeff/jeff.h>
#include <jeff/jlua.h>
#include <jeff/jmemory.h>
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

extern p_flags *PROGRAM_FLAGS;

const k_flags KEYWORD_FLAGS = {
  .VERBOSE = "-v\0",
  .LIBS = "-l\0",
};

void lua_err(lua_State *L, const char *fmt, ...) {
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
    char *str = argv[i];

    if (!strcmp(KEYWORD_FLAGS.VERBOSE, str)) {
      PROGRAM_FLAGS->VERBOSE = JTRUE;
    } else if (!strcmp(KEYWORD_FLAGS.LIBS, str)) {
      PROGRAM_FLAGS->LIBS = JTRUE;
    } else {
      free(PROGRAM_FLAGS);
      err("Invalid argument `%s`\n", str);
      die(127, NULL);
    }
  }
}

int main(int argc, char **argv) {
  init_p_flags();

  argc--;
  parse_argv((uint)argc, argv);
  lua_State *L = init_lua_state();

  lua_close(L);
  return 0;
}
