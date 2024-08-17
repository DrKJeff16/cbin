#ifndef JEFF_H
#define JEFF_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <sys/types.h>

typedef enum _jbool {
  JFALSE = 0,
  JTRUE = 1,
} jbool;

#ifndef PI
#define PI 3.14159
#endif /* !PI */

/* libjoperators */
jbool jxor(const jbool x, const jbool y);

/* libjerr */
void err(const char *fmt, const char *msg);
void verr(const char *fmt, ...);
void exec_verr(void (*fun)(void), const char *fmt, ...);

/* libjdie */
void die(const int status, const char *msg);
void vdie(const int status, const char *fmt, ...);
void exec_vdie(const int status, void (*fun)(void), const char *fmt, ...);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !JEFF_H */
