#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jeff/jeff.h>
#include <jeff/jmemory.h>
#include <jeff/jrandom.h>
#include <jeff/cointoss.h>

CHOICES *init_choices(void) {
  CHOICES *c = MALLOC(CHOICES);
  c->TAILS = 0;
  c->HEADS = 0;

  return c;
}

void decide(const jbool x, CHOICES *c) {
  switch (x) {
    case JTRUE:
      c->HEADS++;
      break;
    case JFALSE:
    default:
      c->TAILS++;
      break;
  }
}

jbool toss(void) {
  return fd_rand(1, 0);
}

void final_decide(const CHOICES *const c, char **const coin) {
  if (null_ptr(coin)) {
    die(1, "No coin to print");
  }

  if (c->HEADS > c->TAILS) {
    printf("%s\n", coin[1]);
  } else if (c->TAILS > c->HEADS) {
    printf("%s\n", coin[0]);
  } else {
    printf("%s\n", coin[toss()]);
  }
}

int main(int argc, char **argv) {
  argc--;

  if (argc != 2) {
    vdie(127, "(main): Need two arguments, no more, no less (got %d)\n", argc);
  }

  CHOICES *c = init_choices();

  char **coin = CALLOC(char *, 2);
  for (size_t i = 0; i < 2; i++) {
    coin[i] = CALLOC(char, 1024);
  }

  for (size_t i = 0; i < 2; i++) {
    coin[i] = REALLOC(coin[i], char, strlen(argv[i + 1]) + 1);
    if (null_ptr(stpcpy(coin[i], argv[i + 1]))) {
      free(coin[1]);
      free(coin[0]);
      free(coin);
      free(c);
      vdie(2, "Unable to copy string to new array");
    }
  }

  for (J_ULLONG i = 0L; i < 100000L; i++) {
    decide(toss(), c);
  }

  final_decide(c, coin);

  free(coin[1]);
  free(coin[0]);
  free(coin);
  free(c);

  return 0;
}

/// vim:ts=2:sts=2:sw=2:et:ai:si:sta:noci:nopi:
