#ifndef JEFF_H
#define JEFF_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <sys/types.h>

typedef uint jbool;

#ifndef PI
#define PI 3.14159
#endif // !PI

jbool jxor(const jbool x, const jbool y);
void err(const char *msg);
void die(const int status, const char *msg);

static void die_exec(const int status, const char *msg, void (*fun)(void));

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !JEFF_H
