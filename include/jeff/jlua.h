#if !defined(JEFF_LUA_H)
#define JEFF_LUA_H 1

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include <lua.h>
#include "jtypes.h"

lua_State *init_lua_state(void);
void parse_argv(const j_uint argc, char **const argv);

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
void new_op_buf(jlua_op_buf *const predecessor, lua_State *L, j_ullong *const index);
/**
 * Initialize an empty jlua operator buffer
 */
jlua_op_buf *init_op_buf(lua_State *L);

void fix_buf_indeces(jlua_op_buf *const ptr, lua_State *L);

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

j_ullong op_buf_len(jlua_op_buf *const ptr, lua_State *L);

jlua_op_buf *insert_op_buf(jlua_op_buf *const ptr, lua_State *L);
void lua_op(lua_State *L, jlua_op_buf *const buf);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* !JEFF_LUA_H */

/// vim:ts=2:sts=2:sw=2:et:ai:si:sta:noci:nopi:
