#if !defined(JSTRING_H)
#define JSTRING_H 1

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include "jtypes.h"

jbool str_startswith(char *const str, char *const start);

void reverse_str(char *str);
char *str_reversed(char *const str);
void str_append_nul(char *str);
jbool compare_strv(char **const argv, const j_ulong len);
char **filter_argv(const j_ulong argc, char **argv);

char *dedup_str(char *const str);

/// Source - https://stackoverflow.com/a
/// Posted by BLUEPIXY
/// Retrieved 2025-12-05, License - CC BY-SA 3.0
char *str_rep(const char *const s, const size_t n);

jbool in_str(char *const str, const char *const c);
jbool is_lower(char *const str);
jbool is_upper(char *const str);
jbool check_jarg(const char *arg, char **argv, const j_uint argc);

void capitalize(char *str);
void upperize(char *str);
void lowerize(char *str);

void j_lstrip(const char c, char *str);
void j_rstrip(const char c, char *str);
void j_strip(const char c, char *str);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* !JSTRING_H */

/// vim:ts=2:sts=2:sw=2:et:ai:si:sta:
