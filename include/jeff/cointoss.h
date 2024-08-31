#ifndef COINTOSS_H
#define COINTOSS_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "jeff.h"

typedef struct {
  J_ULLONG TAILS;
  J_ULLONG HEADS;
} CHOICES;

void decide(const jbool x, CHOICES *c);
jbool toss(int fd);
void final_decide(int fd, CHOICES *const c, char **const coin);
CHOICES *init_choices(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !COINTOSS_H */

/// vim:ts=4:sts=4:sw=4:et:ai:si:sta:noci:nopi:
