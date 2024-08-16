#ifndef JEFF_H
#error "Header `jeff.h` must be included first"
#endif /* !JEFF_H */

#ifndef JEFF_LUA_H
#define JEFF_LUA_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <sys/types.h>
#include <lua.h>

lua_State *init_lua(const jbool with_libs);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !JEFF_LUA_H */
