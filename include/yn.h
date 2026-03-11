#if !defined(YES_NO_H)
#define YES_NO_H 1

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include <jeff/jtypes.h>

struct arguments {
  jbool invert;
  int code;
  char *args;
};

typedef struct arguments arg_data;

char *get_no_args(char **const argv, const size_t argc);
void yes_no(arg_data *arguments);
static void prompt(char *restrict msg, const jbool negative);
static arg_data init_args(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* !YES_NO_H */

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
