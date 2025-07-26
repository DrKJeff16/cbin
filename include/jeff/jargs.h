#if !defined(JARGS_H)

#define JARGS_H 1

#include <argp.h>
#include "jtypes.h"

typedef enum _mode_enum {
  CHARACTER_MODE,
  WORD_MODE,
  LINE_MODE,
} jmode_t;

typedef struct _args {
  jmode_t mode;
  jbool case_sensitive;
} argument_t;

typedef struct argp argp_t;
typedef struct argp_option argp_opt_t;

static error_t parse_opt(int key, char *arg, struct argp_state *state);

#endif /* !JARGS_H */
