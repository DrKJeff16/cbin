#ifndef JEFF_H
#error "Header `jeff.h` must be included first"
#endif /* !JEFF_H */

#ifndef JMEMORY_H
#error "Header `jmemory.h` must be included first"
#endif /* !JMEMORY_H */

#ifndef JSTRING_H
#define JSTRING_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <sys/types.h>

typedef struct _char_ptrs {
  char *s1;
  char *s2;
} char_ptrs;

jbool compare_two_strings(char *s1, char *s2);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !JSTRING_H */
