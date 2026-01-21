#if !defined(COINTOSS_H)
#define COINTOSS_H 1

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include <jeff/jtypes.h>

typedef struct arguments {
  jbool urandom;
  jbool total;
  jbool verbose;
  j_ullong rep;
  size_t n_args;
  size_t count;
  char *args[2];
} arg_data;

typedef struct _choices {
  j_ullong TAILS;
  j_ullong HEADS;
} coin_t;

jbool fd_toss(const int fd);
coin_t *init_choices(void);

void decide(const jbool x, coin_t *c);
void verdict(const int fd, coin_t *c, char *coin[2], char **total, const size_t n);
void show_total(char *choices[2], char **total, size_t n);

static void gc(char **coin, coin_t *c);
static arg_data init_args(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* !COINTOSS_H */

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
