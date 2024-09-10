#ifndef JSTRING_H
#define JSTRING_H 1

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include "jeff.h"

typedef struct _char_ptrs {
  const char *s1;
  const char *s2;
} char_ptrs;

char *str_reversed(char *const str);
void str_append_nul(char *str);
jbool compare_strv(char **const argv, const J_ULONG len);
char **filter_argv(const J_ULONG argc, char **argv);

char *dedup_str(char *const str);

jbool is_lower(char *const str);
jbool is_upper(char *const str);
void capitalize(char *str, jbool *use_dot);
void upperize(char *str);
void lowerize(char *str);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* !JSTRING_H */

/// vim:ts=4:sts=4:sw=4:et:ai:si:sta:noci:nopi:
