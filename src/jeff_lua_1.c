#include <errno.h>
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jeff/jeff.h>
#include <jeff/jmemory.h>
#include <jeff/jlua.h>

static p_flags *PROGRAM_FLAGS = NULL;

const k_flags KEYWORD_FLAGS = {
  .VERBOSE = "-v",
  .LIBS = "-l",
};

static void stack_dump(lua_State *L) {
  int i = 1, top = lua_gettop(L);

  if (top >= i) {
    printf("| ");
  }

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
        printf("%g", lua_tonumberx(L, i, NULL));
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
  if (!null_ptr(fmt)) {
    va_list argp;

    va_start(argp, fmt);
    vfprintf(stderr, fmt, argp);
    va_end(argp);
  }

  if (!null_ptr(L)) {
    lua_close(L);
  }

  free(PROGRAM_FLAGS);

  if (errno) {
    vdie(errno, "%s\n", strerror(errno));
  }

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
        vdie(1, "Invalid argument `%s`\n", str);
      }
    }
  }
}

int main(int argc, char **argv) {
  init_p_flags();

  argc--;
  parse_argv((uint)argc, argv);
  lua_State *L = init_lua_state();

  stack_dump(L);
  lua_pushboolean(L, JTRUE);
  stack_dump(L);
  lua_pushnumber(L, 10);
  stack_dump(L);
  lua_pushnil(L);
  stack_dump(L);
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

  jbool *x = MALLOC(jbool);
  *x = JTRUE;

  j_ullong idx = 0;

  jlua_op_buf *op_buf = init_op_buf(L);

  printf("Op Buffer ==> %p\n", JCAST(void *, op_buf));
  op_buf->index = idx;
  op_buf->_type = JLUA_BOOL;
  op_buf->_operator = NOOP;
  op_buf->data = x;

  jlua_op_buf *buf_head = op_buf, *placeholder = NULL;
  idx++;

  new_op_buf(buf_head, L, &idx);
  idx++;
  placeholder = buf_head->_next;
  buf_head = placeholder;
  new_op_buf(buf_head, L, &idx);
  idx++;
  placeholder = buf_head->_next;
  buf_head = placeholder;

  printf("First address ==> %p\n", JCAST(void *, first_op_buf(op_buf, L)));
  printf("Last address ==> %p\n", JCAST(void *, last_op_buf(op_buf, L)));

  kill_op_buf(op_buf, L);

  lua_close(L);
  return 0;
}

/// vim:ts=2:sts=2:sw=2:et:ai:si:sta:noci:nopi:
