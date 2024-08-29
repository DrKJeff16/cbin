#ifndef JEFF_H
#define JEFF_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef enum _jbool {
  JFALSE = 0,
  JTRUE = 1,
} jbool;

#ifndef J_ULLONG
#define J_ULLONG unsigned long long
#endif /* !J_ULLONG */

#ifndef J_LLONG
#define J_LLONG long long
#endif /* !J_LLONG */

#ifndef J_ULONG
#define J_ULONG unsigned long
#endif /* !J_ULONG */

#ifndef J_UINT
#define J_UINT unsigned int
#endif /* !J_UINT */

#ifndef J_LUINT
#define J_LUINT long unsigned int
#endif /* !J_LUINT */

#ifndef J_UCHAR
#define J_UCHAR unsigned char
#endif /* !J_UCHAR */

#ifndef J_LINT
#define J_LINT long int
#endif /* !J_LINT */

#define J_PI_F 3.14159265358979323846

#define J_PI_LF 3.1415926535897932384626433832795028841971693993

#define J_TAU_F 2. * J_PI_F
#define J_TAU_LF 2. * J_PI_LF

/* joperators */
jbool jxor(const J_ULLONG x, const J_ULLONG y);
jbool null_ptr(void *const ptr);

/* jerr */
void err(char *const fmt, char *const msg);
void verr(char *const fmt, ...);
void exec_verr(void (*fun)(void), char *const fmt, ...);

/* jdie */
void die(const int status, char *const msg);
void vdie(const int status, char *const fmt, ...);
void exec_vdie(const int status, void (*fun)(void), char *const fmt, ...);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !JEFF_H */

/// vim:ts=4:sts=4:sw=4:et:ai:si:sta:noci:nopi:
