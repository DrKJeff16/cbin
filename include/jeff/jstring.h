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

char *str_reversed(char *const str);
void str_append_nul(char *str);
jbool compare_strv(char **const argv, const size_t len);
char **filter_argv(const size_t argc, char **argv);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !JSTRING_H */

/// vim:ts=4:sts=4:sw=4:et:ai:si:sta:noci:nopi:
