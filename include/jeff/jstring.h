#if !defined(JSTRING_H)
#define JSTRING_H 1

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include "jtypes.h"

void reverse_str(char *str);
char *str_reversed(char *const str);
void str_append_nul(char *str);
jbool compare_strv(char **const argv, const j_ulong len);
char **filter_argv(const j_ulong argc, char **argv);

char *dedup_str(char *const str);

jbool is_lower(char *const str);
jbool is_upper(char *const str);
jbool check_jarg(const char *arg, char **argv, const j_uint argc);

void capitalize(char *str, jbool *use_dot);
void upperize(char *str);
void lowerize(char *str);

void lstrip(const char c, char *str);
void rstrip(const char c, char *str);
void strip(const char c, char *str);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* !JSTRING_H */

/// vim:ts=2:sts=2:sw=2:et:ai:si:sta:noci:nopi:
