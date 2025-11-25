#if !defined(COINTOSS_H)
#define COINTOSS_H 1

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include <jeff/jeff.h>

typedef struct _choices {
  j_ullong TAILS;
  j_ullong HEADS;
} coin_t;

jbool fd_toss(const int fd);
coin_t *init_choices(void);
char **init_decisions(int fd, coin_t *c, char **argv);

void decide(const jbool x, coin_t *c);
void verdict(const int fd, coin_t *const c, char **const coin);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* !COINTOSS_H */

/// vim:ts=2:sts=2:sw=2:et:ai:si:sta:
