#if !defined(JLUAJIT_H)
#define JLUAJIT_H

#if defined(__cplusplus)
extern "C" {
#endif

#include <jeff/jmemory.h>
#include <jeff/jtypes.h>
#include <lauxlib.h>
#include <lua.h>
#include <luajit.h>
#include <lualib.h>

lua_State *new_lua_state(void);
void jlua_die(const int code, lua_State *L, char *const fmt, ...);
void jlua_push(lua_State *L, const jlua_type type, void *item, ...);

#if defined(__cplusplus)
}
#endif

#endif /* !JLUAJIT_H */

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
