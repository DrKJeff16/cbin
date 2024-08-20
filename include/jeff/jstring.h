#ifndef JSTRING_H
#define JSTRING_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <sys/types.h>

#include "jeff.h"

typedef struct _char_ptrs {
  const char *s1;
  const char *s2;
} char_ptrs;

void str_append_nul(char *str);
jbool compare_two_strings(const char *s1, const char *s2);
jbool compare_strv(const char **argv, const size_t len);
char **filter_argv(const uint argc, char **argv);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !JSTRING_H */

/// vim:ts=2:sts=2:sw=2:et:ai:si:sta:noci:noet:
