#ifndef COINTOSS_H
#define COINTOSS_H

#include <stdbool.h>
#include <sys/types.h>

typedef struct {
    uint TAILS;
    uint HEADS;
} CHOICES;

static void seed(bool *seeded);
static void decide(const uint x, CHOICES *c);
static void final_decide(CHOICES *c, char *tails_msg, char *heads_msg);
static char *error_msg(void);
uint toss(void);

#endif // !COINTOSS_H
