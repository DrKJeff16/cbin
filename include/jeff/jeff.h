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

#ifndef J_UULONG
#define J_UULONG unsigned long long
#endif // !J_UULONG

#ifndef J_ULONG
#define J_ULONG unsigned long
#endif // !J_ULONG

#ifndef J_UINT
#define J_UINT unsigned int
#endif // !J_UINT

#ifndef J_LUINT
#define J_LUINT long unsigned int
#endif // !J_LUINT

#ifndef J_UCHAR
#define J_UCHAR unsigned char
#endif // !J_UCHAR

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
