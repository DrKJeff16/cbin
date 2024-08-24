#ifndef COINTOSS_H
#define COINTOSS_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <sys/types.h>

#include "jeff.h"

typedef struct {
  J_ULLONG TAILS;
  J_ULLONG HEADS;
} CHOICES;

void seed(void);
void decide(const jbool x, CHOICES *c);
jbool toss(void);
void final_decide(const CHOICES *c, char **coin);
CHOICES *init_choices(void);

static jbool SEEDED = JFALSE;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !COINTOSS_H */

/// vim:ts=4:sts=4:sw=4:et:ai:si:sta:noci:nopi:
