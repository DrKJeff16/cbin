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

void decide(const jbool x, coin_t *c);
jbool fd_toss(int fd);
void final_decide(int fd, coin_t *const c, char **const coin);
coin_t *init_choices(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* !COINTOSS_H */

/// vim:ts=2:sts=2:sw=2:et:ai:si:sta:noci:nopi:
