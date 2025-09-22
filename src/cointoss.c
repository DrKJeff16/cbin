#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jeff/jeff.h>
#include <cointoss.h>

/* @brief Garbage collector
 *
 */
static void gc(char **coin, coin_t *c) {
  free(c);

  free(coin[JTRUE]);
  free(coin[JFALSE]);
  free(coin);
}

coin_t *init_choices(void) {
  coin_t *c = MALLOC(coin_t);

  c->TAILS = 0;
  c->HEADS = 0;

  return c;
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
    default:
      c->HEADS++;
      break;
  }
}

jbool fd_toss(int fd) {
  if (fd < 0) {
    j_errno_vdie(JTRUE, EBADFD, "(fd_toss): %s (fd: %d)\n", "File descriptor unavailable!", fd);
  }

  return fd_urand(fd, JFALSE, JTRUE) ? JTRUE : JFALSE;
}

void verdict(int fd, coin_t *const c, char **const coin) {
  if (fd < 0) {
    j_errno_vdie(JTRUE, EBADFD, "(verdict): %s (fd: %d)\n", "File descriptor unavailable!", fd);
  }
  if (null_ptr(coin)) {
    j_errno_vdie(JTRUE, EFAULT, "(verdict): %s\n", "No coin to print!");
  }
  if (null_ptr(c)) {
    j_errno_vdie(JTRUE, EFAULT, "(verdict): %s\n", "No available choices!");
  }

  char *result = coin[(c->HEADS > c->TAILS) ? JTRUE : ((c->TAILS > c->HEADS) ? JFALSE : fd_toss(fd))];

  printf("%s\n", result);
}

int main(int argc, char **argv) {
  argc--;

  if (check_jarg("-h", argv, argc)) {
    return 0;
  }

  if (argc != 2) {
    j_errno_vdie(127, ENOTSUP, "(cointoss): Need two arguments, no more, no less (got %d)!\n", argc);
  }

  int fd = open("/dev/urandom", O_RDONLY);
  if (fd < 0) {
    j_errno_vdie(127, ENOENT, "(cointoss): `/dev/urandom` is unavailable (fd: %d)!\n", fd);
  }

  coin_t *c = init_choices();

  char **coin = CALLOC(char *, 2);

  for (size_t i = 0; i <= JTRUE; i++) {
    coin[i] = CALLOC(char, strlen(argv[i + 1]) + 1);

    char *chr = stpcpy(coin[i], argv[i + 1]);

    if (null_ptr(chr)) {
      gc(coin, c);
      close(fd);

      j_errno_vdie(2, EBADE, "(cointoss): %s\n", "Unable to copy string to new array!");
    }
  }

  for (j_ullong i = 0; i < 1000000 && fd >= 0; i++) {
    decide(fd_toss(fd), c);
  }

  verdict(fd, c, coin);

  gc(coin, c);

  if ((close(fd)) != 0) {
    die(JTRUE, "File descriptor could not be closed correctly!\n");  /// Unsuccessful exit
  }

  die(JFALSE, NULL);  /// Successful exit
}

/// vim:ts=2:sts=2:sw=2:et:ai:si:sta:noci:nopi:
