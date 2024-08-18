#ifndef JEFF_LUA_H
#define JEFF_LUA_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "jeff.h"
#include <sys/types.h>
#include <lua.h>

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
  unsigned long long index;
  jlua_operator _operator;
  jlua_type _type;
  void *data;
  struct _jlua_op *_next;
} jlua_op_buf;

typedef struct _jlua_state_buf {
  lua_State *L;
  uint stack_len;
} jlua_sbuf;

static p_flags *PROGRAM_FLAGS;

lua_State *init_lua_state(void);
void parse_argv(const uint argc, char **argv);

/**
 * Print an error message, shut down the Lua state and exit with code 1
 */
void lua_err(lua_State *L, const char *fmt, ...);

/**
 * Generate a new jlua operator buffer to be indexed
 */
void new_op_buf(jlua_op_buf *predecessor, const unsigned long long *i);
/**
 * Initialize an empty jlua operator buffer
 */
jlua_op_buf *init_op_buf(void);
/**
 * Append new buffer to a jlua operator buffer
 *
 * @param ptr The pointer to the linked list to be added
 *
 * @return The memory address of the appended struct, not any of the preceding ones
 */
jlua_op_buf *append_op_buf(jlua_op_buf *ptr);
/**
 * Pop the last element of a jlua operation buffer
 *
 * @param ptr The pointer to the linked list to be added
 * @return The memory address of the appended struct, not any of the preceding ones
 */
jlua_op_buf *pop_op_buf(jlua_op_buf *ptr);
void lua_op(lua_State *L, jlua_op_buf *buf);

jlua_sbuf *init_jlua_sbuf(lua_State *L, const size_t stack_len);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !JEFF_LUA_H */
