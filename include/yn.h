#if !defined(YES_NO_H)
#define YES_NO_H 1

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#define YN_MAX_EC 300

#include <jeff/jtypes.h>

struct arguments {
  char **args;
  int code;
  j_ullong tries;
  jbool invert;
  size_t n_args;
};

typedef struct arguments arg_data;

char *get_no_args(char **const argv, const size_t argc);
void yes_no(arg_data *arguments);
static void prompt(char **restrict msg, const size_t n, const jbool negative);
static arg_data init_args(void);
static void gc_exit(arg_data *arguments, const int code);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* !YES_NO_H */

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
