#ifndef JEFF_LUA_H
#define JEFF_LUA_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <lua.h>

#include "jeff.h"

typedef struct _p_flags {
  jbool VERBOSE;
  jbool LIBS;
} p_flags;

typedef struct _k_flags {
  const char VERBOSE[3];
  const char LIBS[3];
} k_flags;

typedef enum __jlua_type {
  JLUA_NIL = 0,
  JLUA_BOOL,
  JLUA_NUM,
  JLUA_STR,
  JLUA_LSTR,
} jlua_type;

typedef enum __jlua_operator {
  NOOP = 0,
  PUSH,
  CHECK_STACK,
} jlua_operator;

typedef struct _jlua_op {
  struct _jlua_op *_prev;
  J_ULLONG index;
  jlua_operator _operator;
  jlua_type _type;
  void *data;
  struct _jlua_op *_next;
} jlua_op_buf;

lua_State *init_lua_state(void);
void parse_argv(const J_UINT argc, char **const argv);

/**
 * Print an error message, shut down the Lua state and exit with code 1
 */
void lua_err(lua_State *L, char *const fmt, ...);

char *jlua_op_char(const jlua_operator x);
char *jlua_type_char(const jlua_type x);

jlua_op_buf *first_op_buf(jlua_op_buf *const ptr, lua_State *L);
jlua_op_buf *last_op_buf(jlua_op_buf *const ptr, lua_State *L);
void kill_op_buf(jlua_op_buf *const ptr, lua_State *L);

/**
 * Generate a new jlua operator buffer to be indexed
 */
void new_op_buf(jlua_op_buf *const predecessor, lua_State *L, J_ULLONG *const index);
/**
 * Initialize an empty jlua operator buffer
 */
jlua_op_buf *init_op_buf(lua_State *L);
/**
 * Append new buffer to a jlua operator buffer
 *
 * @param ptr The pointer to the linked list to be added
 *
 * @return The memory address of the appended struct, not any of the preceding
 * ones
 */
jlua_op_buf *append_op_buf(jlua_op_buf *const ptr, lua_State *L);

void op_buf_iprint(jlua_op_buf *const ptr, lua_State *L);

J_ULLONG op_buf_len(jlua_op_buf *const ptr, lua_State *L);

jlua_op_buf *insert_op_buf(jlua_op_buf *const ptr, lua_State *L);
void lua_op(lua_State *L, jlua_op_buf *const buf);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !JEFF_LUA_H */

/// vim:ts=4:sts=4:sw=4:et:ai:si:sta:noci:nopi:
