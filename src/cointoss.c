#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
/* #include <string.h> */
#include <time.h>
#include <jeff/jeff.h>
#include <jeff/jmemory.h>
#include <jeff/cointoss.h>

static void seed(jbool *seeded) {
    if (!(*seeded)) {
        srand(time(NULL));
        *seeded = 1;
    }
}

static void decide(const uint x, CHOICES *c) {
    switch(x) {
        case 1:
            c->HEADS++;
            break;
        case 0:
        default:
            c->TAILS++;
            break;
    }
}

static void final_decide(CHOICES *c, char *tails_msg, char *heads_msg) {
    if (c->HEADS > c->TAILS) {
        printf("%s\n", tails_msg);
    } else if (c->TAILS > c->HEADS) {
        printf("%s\n", heads_msg);
    } else {
        char **msgs = CALLOC(char*, 2);
        char **og = msgs;

        *msgs = tails_msg;
        ++msgs;
        *msgs = heads_msg;
        msgs = og;

        printf("%s\n", msgs[toss()]);

        free(msgs);
    }
}

static char *error_msg(void) {
    char *result = "Need two arguments";

    return result;
}

uint toss(void) {
    return (uint)(rand() % 2);
}

int main(int argc, char **argv) {
    argc--;

    if (argc != 2) {
        die(127, error_msg());
    }

    jbool *seeded = CALLOC(jbool, 1);
    *seeded = 0;

    seed(seeded);

    char *tails_msg, *heads_msg;
    char **argv_og = argv;

    (++argv);
    tails_msg = *argv;
    (++argv);
    heads_msg = *argv;

    argv = argv_og;

    CHOICES *c = MALLOC(CHOICES);
    c->TAILS = 0;
    c->HEADS = 0;

    for (unsigned long long i = 0L; i < 100000L; i++ ){
        decide(toss(), c);
    }

    final_decide(c, tails_msg, heads_msg);

    free(c);
    free(seeded);

    return 0;
}
