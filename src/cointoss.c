#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
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
    case JFALSE:
      c->TAILS++;
      break;
    case JTRUE:
    default:
      c->HEADS++;
      break;
  }
}

jbool toss(int fd) {
  if (fd < 0) {
    perror("toss");
    verr("(toss): %s (fd: %d)\n", "File descriptor unavailable", fd);
    return JFALSE;
  }

  return fd_urand(fd, 0, 1) ? JTRUE : JFALSE;
}

void final_decide(int fd, CHOICES *const c, char **const coin) {
  if (fd < 0) {
    vdie(1, "(toss): %s\n%s (fd: %d)\n", strerror(EBADFD), "File descriptor unavailable", fd);
  }
  if (null_ptr(coin)) {
    vdie(1, "%s\n%s\n", strerror(EFAULT), "No coin to print");
  }
  if (null_ptr(c)) {
    vdie(1, "(final_decide): %s\n%s\n", strerror(EFAULT), "No choices to make a decision from");
  }

  char *result = coin[toss(fd)];
  if (c->HEADS > c->TAILS) {
    result = coin[1];
  } else if (c->TAILS > c->HEADS) {
    result = coin[0];
  }

  printf("%s\n", result);
}

int main(int argc, char **argv) {
  argc--;

  if (argc != 2) {
    vdie(127, "(cointoss): %s\n%s (got %d)\n", strerror(EPERM),
         "Need two arguments, no more, no less", argc);
  }

  int fd = open("/dev/urandom", O_RDONLY);
  if (fd < 0) {
    vdie(127, "(cointoss): %s\n%s (fd: %d)\n", strerror(ENOENT), "`/dev/urandom` is unavailable",
         fd);
  }

  CHOICES *c = init_choices();

  char **coin = CALLOC(char *, 2);

  for (size_t i = 0; i < 2; i++) {
    coin[i] = CALLOC(char, 1024);
  }

  for (size_t i = 0; i < 2; i++) {
    coin[i] = REALLOC(coin[i], char, strlen(argv[i + 1]) + 1);

    char *chr = stpcpy(coin[i], argv[i + 1]);
    if (null_ptr(chr)) {
      free(coin[1]);
      free(coin[0]);
      free(coin);
      free(c);

      close(fd);

      vdie(2, "(cointoss): %s\n%s\n", strerror(EBADE), "Unable to copy string to new array");
    }
  }

  for (J_ULLONG i = 0; i < 1000000 && fd >= 0; i++) {
    decide(toss(fd), c);
  }

  final_decide(fd, c, coin);

  free(coin[1]);
  free(coin[0]);
  free(coin);
  free(c);

  close(fd);

  return 0;
}

/// vim:ts=2:sts=2:sw=2:et:ai:si:sta:noci:nopi:
