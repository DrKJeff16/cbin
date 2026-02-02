#if !defined(SHRUG_H)
#define SHRUG_H 1

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include <jeff/jtypes.h>

typedef struct arguments {
  jbool list;
  size_t n_args;
  char *args;
} arg_data;

static arg_data init_args(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* !SHRUG_H */

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
