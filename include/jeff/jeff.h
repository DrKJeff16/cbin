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
#endif  // !J_UULONG

#ifndef J_ULONG
#define J_ULONG unsigned long
#endif  // !J_ULONG

#ifndef J_UINT
#define J_UINT unsigned int
#endif  // !J_UINT

#ifndef J_LUINT
#define J_LUINT long unsigned int
#endif  // !J_LUINT

#ifndef J_UCHAR
#define J_UCHAR unsigned char
#endif  // !J_UCHAR

#ifndef PI
#define PI 3.14159f
#endif /* !PI */

/* libjoperators */
jbool jxor(const jbool x, const jbool y);

/* libjerr */
void err(char *const fmt, char *const msg);
void verr(char *const fmt, ...);
void exec_verr(void (*fun)(void), char *const fmt, ...);

/* libjdie */
void die(const int status, char *const msg);
void vdie(const int status, char *const fmt, ...);
void exec_vdie(const int status, void (*fun)(void), char *const fmt, ...);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !JEFF_H */

/// vim:ts=4:sts=4:sw=4:et:ai:si:sta:noci:nopi:
