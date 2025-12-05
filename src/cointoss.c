#include <fcntl.h>
#include <unistd.h>
#include <asm-generic/errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jeff/jeff.h>
#include <cointoss.h>

static void usage(int code) {
  char *txt = "cointoss <X> <Y> [-h]\n\n        -h                 print usage\n";

  if (!code) {
    printf("%s\n", txt);
    return;
  }

  j_verr("%s\n", txt);
}

/* @brief Garbage collector
 *
 */
static void gc(char **coin, coin_t *c) {
  void **garbage = CALLOC(void *, 4);
  garbage[0] = (void *)c;
  garbage[1] = (void *)coin[JTRUE];
  garbage[2] = (void *)coin[JFALSE];
  garbage[3] = (void *)coin;

  j_gc(garbage, 4);
}

coin_t *init_choices(void) {
  coin_t *c = MALLOC(coin_t);

  c->TAILS = 0;
  c->HEADS = 0;

  return c;
}

char **init_decisions(int fd, coin_t *c, char **argv) {
  char **decisions = CALLOC(char *, 2);
  for (size_t i = 0; i <= JTRUE; i++) {
    decisions[i] = CALLOC(char, strlen(argv[i + 1]) + 1);
    char *chr = stpcpy(decisions[i], argv[i + 1]);
    if (null_ptr(chr)) {
      gc(decisions, c);
      close(fd);

      j_errno_vdie(2, EBADE, "(cointoss): %s\n", "Unable to copy string to new array!");
    }
  }

  return decisions;
}

void decide(const jbool x, coin_t *c) {
  if (null_ptr(c)) {
    j_errno_die(127, EFAULT, "Choices struct is NULL!");
  }

  switch (x) {
    case JFALSE:
      c->TAILS++;
      break;
    case JTRUE:
      c->HEADS++;
      break;
  }
}

jbool fd_toss(const int fd) {
  if (fd < 0) {
    j_errno_vdie(JTRUE, EBADFD, "(fd_toss): %s (fd: %d)\n", "File descriptor unavailable!", fd);
  }

  return fd_urand(fd, JFALSE, JTRUE) ? JTRUE : JFALSE;
}

void verdict(const int fd, coin_t *const c, char **const coin) {
  if (fd < 0) {
    gc(coin, c);
    j_errno_vdie(JTRUE, EBADFD, "(verdict): %s (fd: %d)\n", "File descriptor unavailable!", fd);
  }
  if (null_ptr(coin)) {
    gc(coin, c);
    j_errno_vdie(JTRUE, EFAULT, "(verdict): %s\n", "No coin to print!");
  }
  if (null_ptr(c)) {
    gc(coin, c);
    j_errno_vdie(JTRUE, EFAULT, "(verdict): %s\n", "No available choices!");
  }

  printf("%s\n", coin[(c->HEADS > c->TAILS) ? JTRUE : ((c->TAILS > c->HEADS) ? JFALSE : fd_toss(fd))]);
}

int main(int argc, char **argv) {
  argc--;

  if (check_jarg("-h", argv, argc)) {
    usage(JFALSE);
    die(JFALSE, NULL);
  }
  if (argc != 2) {
    usage(127);
    die(127, NULL);
  }

  int fd = open("/dev/urandom", O_RDONLY);
  if (fd < 0) {
    j_errno_vdie(127, ENOENT, "(cointoss): `/dev/urandom` is unavailable (fd: %d)!\n", fd);
  }

  coin_t *c = init_choices();
  char **coin = init_decisions(fd, c, argv);

  for (j_ullong i = 0; i < 1000000 && fd >= 0; i++) {
    decide(fd_toss(fd), c);
  }

  verdict(fd, c, coin);
  gc(coin, c);

  int closed = close(fd);
  if (closed != 0) {
    vdie(JTRUE, "Code %d: File descriptor could not be closed correctly!\n", closed);
  }

  die(JFALSE, NULL);
}

/// vim:ts=2:sts=2:sw=2:et:ai:si:sta:
