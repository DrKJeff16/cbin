#ifndef COINTOSS_H
#define COINTOSS_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <sys/types.h>

#include "jeff.h"

typedef struct {
  uint TAILS;
  uint HEADS;
} CHOICES;

void seed(void);
void decide(const uint x, CHOICES *c);
void final_decide(CHOICES *c, char *tails_msg, char *heads_msg);
uint toss(void);

static jbool SEEDED = JFALSE;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !COINTOSS_H */

/// vim:ts=2:sts=2:sw=2:et:ai:si:sta:noci:noet:
