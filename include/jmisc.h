#if !defined(JMISC_H)
#define JMISC_H 1

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include <jeff/jtypes.h>

struct arguments {
  jbool verbose;
  size_t n_args;
  char **args;
};

typedef struct arguments arg_data;

static arg_data init_args(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* !JMISC_H */
