#ifndef COINTOSS_H
#define COINTOSS_H

#include <stdbool.h>
#include <sys/types.h>

typedef struct {
    uint TAILS;
    uint HEADS;
} CHOICES;

static void seed(bool*);
static void decide(const uint, CHOICES*);
static void final_decide(CHOICES*, char*, char*);
static char *error_msg(void);
unsigned int toss(void);

#endif // !COINTOSS_H
