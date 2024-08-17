#include <jeff/jeff.h>      // for _jbool, die, err
#include <jeff/jeff_lua.h>  // for p_flags, k_flags, init_lua, parse_argv
#include <jeff/jmemory.h>   // for MALLOC
#include <lauxlib.h>        // for luaL_newstate
#include <lua.h>            // for lua_State, lua_close
#include <lualib.h>         // for luaL_openlibs
#include <stdio.h>          // for printf, NULL
#include <stdlib.h>         // for free
#include <string.h>         // for strcmp
#include <sys/types.h>      // for uint

extern p_flags *PROGRAM_FLAGS;

const k_flags KEYWORD_FLAGS = {
  .VERBOSE = "-v\0",
  .LIBS = "-l\0",
};

static void init_p_flags(void) {
  PROGRAM_FLAGS = MALLOC(p_flags);
  PROGRAM_FLAGS->VERBOSE = JFALSE;
  PROGRAM_FLAGS->LIBS = JFALSE;
}

lua_State *init_lua(void) {
  lua_State *L = luaL_newstate();

  switch (PROGRAM_FLAGS->LIBS) {
    case JTRUE:
      luaL_openlibs(L);

      if (PROGRAM_FLAGS->VERBOSE == JTRUE) {
        printf("%s\n", "Loading with libs");
      }

      break;
    case JFALSE:
    default:
      break;
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
  lua_State *L = init_lua();

  lua_close(L);
  return 0;
}
