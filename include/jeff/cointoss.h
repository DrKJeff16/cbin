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

void seed(jbool *seeded);
void decide(const uint x, CHOICES *c);
void final_decide(CHOICES *c, char *tails_msg, char *heads_msg);
uint toss(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !COINTOSS_H */
