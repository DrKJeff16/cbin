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

jbool jxor(const jbool x, const jbool y);
void err(const char *msg);
void die(const int status, const char *msg);
int jlog(const int fd, const char *msg);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !JEFF_H */
