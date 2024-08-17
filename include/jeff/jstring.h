#ifndef JSTRING_H
#define JSTRING_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <sys/types.h>
#include <string.h>
#include <jeff/jeff.h>

typedef struct _char_ptrs {
  char *s1;
  char *s2;
} char_ptrs;

jbool compare_two_strings(const char *s1, const char *s2);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !JSTRING_H */
