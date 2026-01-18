#if !defined(YES_NO_H)
#define YES_NO_H 1

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include <jeff/jtypes.h>

typedef struct arguments {
  jbool invert;
  size_t n_args;
  int code;
  char *args[1];
} arg_data;

char *get_no_args(char **const argv, const size_t argc);
static void prompt(const char *restrict msg, const jbool negative);
static arg_data init_args(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* !YES_NO_H */

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
