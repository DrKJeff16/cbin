#ifndef JEFF_H
#error "Header `jeff.h` must be included first"
#endif /* !JEFF_H */

#ifndef COINTOSS_H
#define COINTOSS_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <sys/types.h>

typedef struct {
    uint TAILS;
    uint HEADS;
} CHOICES;

static void seed(jbool *seeded);
static void decide(const uint x, CHOICES *c);
static void final_decide(CHOICES *c, char *tails_msg, char *heads_msg);
static char *error_msg(void);
uint toss(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !COINTOSS_H */
