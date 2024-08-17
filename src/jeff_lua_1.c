#include <jeff/jeff.h>      // for _jbool, die, err
#include <jeff/jlua.h>      // for p_flags, k_flags, init_lua, parse_argv
#include <jeff/jmemory.h>   // for MALLOC
#include <lauxlib.h>        // for luaL_newstate
#include <lua.h>            // for lua_State, lua_close
#include <lualib.h>         // for luaL_openlibs
#include <stdarg.h>         // for va_list, va_start
#include <stdio.h>          // for printf, NULL
#include <stdlib.h>         // for free
#include <string.h>         // for strcmp
#include <sys/types.h>      // for uint

extern p_flags *PROGRAM_FLAGS;

const k_flags KEYWORD_FLAGS = {
  .VERBOSE = "-v\0",
  .LIBS = "-l\0",
};

static void lua_err(lua_State *L, const char *fmt, ...) {
  va_list argp;

  va_start(argp, fmt);
  vfprintf(stderr, fmt, argp);
  va_end(argp);

  lua_close(L);
  free(PROGRAM_FLAGS);

  exit(EXIT_FAILURE);
}

void lua_op(lua_State *L, const jlua_type type, jlua_op_buf *operation, void *data) {
  if (L == NULL) {
    vdie(2, "(jlua_op): %s\n", "Lua state is NULL. Aborting");
  }
  if (operation == NULL) {
    lua_err(L,  "(lua_op): %s\n", "NULL operation is unacceptable");
  }

  if (operation->_next == NULL) {
    append_op_buf(operation);
  }

  switch (type) {
    case JLUA_NIL:
      lua_pushnil(L);
      break;
    case JLUA_BOOL:
      if (data != NULL) {
        lua_pushboolean(L, *(int*)(data));
      }
      break;
    case JLUA_NUM:
      if (data != NULL) {
        lua_pushnumber(L, *(double*)data);
      }
      break;
    case JLUA_LSTR:
      if (data != NULL) {
        const char *str = (char*)data;
        size_t len = strnlen(str, 512);
        lua_pushlstring(L, str, len);
      }
      break;
    case JLUA_STR:
      if (data != NULL) {
        const char *str = (char*)data;
        lua_pushstring(L, str);
      }
      break;
    default:
      lua_err(L, "%s\n", "Invalid operation. Aborting");
      break;
  }

  operation->data = data;
}

static void init_p_flags(void) {
  PROGRAM_FLAGS = MALLOC(p_flags);
  PROGRAM_FLAGS->VERBOSE = JFALSE;
  PROGRAM_FLAGS->LIBS = JFALSE;
}

static lua_State *init_lua_state(void) {
  lua_State *L = luaL_newstate();

  if (PROGRAM_FLAGS->LIBS)
    luaL_openlibs(L);

  if (PROGRAM_FLAGS->VERBOSE) {
    printf("%s\n", "Loading with libs");
  }

  return L;
}

static void parse_argv(const uint argc, char **argv) {
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
