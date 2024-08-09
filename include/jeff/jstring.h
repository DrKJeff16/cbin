#ifndef JEFF_H
#error "Header `jeff.h` must be included first"
#endif /* !JEFF_H */

#ifndef JSTRING_H
#define JSTRING_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <sys/types.h>

uint compare_two_strings(char *s1, char *s2, const uint n);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !JSTRING_H */
