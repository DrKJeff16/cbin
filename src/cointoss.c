#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jeff/jeff.h>
#include <cointoss.h>

coin_t *init_choices(void) {
  coin_t *c = MALLOC(coin_t);

  c->TAILS = 0;
  c->HEADS = 0;

  return c;
}

void decide(const jbool x, coin_t *c) {
  if (null_ptr(c)) {
    errno_die(127, EFAULT, "Choices struct is NULL");
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
    errno_vdie(127, EBADF, "(fd_toss): %s (fd: %d)\n", "File descriptor unavailable");
  }

  return fd_urand(fd, JFALSE, JTRUE) ? JTRUE : JFALSE;
}

void final_decide(int fd, coin_t *const c, char **const coin) {
  if (fd < 0) {
    errno_vdie(JTRUE, EBADFD, "(final_decide): %s (fd: %d)\n", "File descriptor unavailable", fd);
  }

  if (null_ptr(coin)) {
    errno_vdie(JTRUE, EFAULT, "(final_decide): %s\n", "No coin to print");
  }

  if (null_ptr(c)) {
    errno_vdie(JTRUE, EFAULT, "(final_decide): %s\n", "No choices to make a decision from");
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
    errno_vdie(127, ENOTSUP, "(cointoss): %s (got %d)\n", "Need two arguments, no more, no less", argc);
  }

  int fd = open("/dev/urandom", O_RDONLY);
  if (fd < 0) {
    errno_vdie(127, ENOENT, "(cointoss): %s (fd: %d)\n", "`/dev/urandom` is unavailable", fd);
  }

  coin_t *c = init_choices();

  char **coin = CALLOC(char *, 2);

  for (size_t i = 0; i <= JTRUE; i++) {
    coin[i] = CALLOC(char, strlen(argv[i + 1]) + 1);

    char *chr = stpcpy(coin[i], argv[i + 1]);

    if (null_ptr(chr)) {
      free(coin[JTRUE]);
      free(coin[JFALSE]);
      free(coin);
      free(c);

      close(fd);

      errno_vdie(2, EBADE, "(cointoss): %s\n", "Unable to copy string to new array");
    }
  }

  for (j_ullong i = 0; i < 1000000 && fd >= 0; i++) {
    decide(fd_toss(fd), c);
  }

  final_decide(fd, c, coin);

  free(coin[JTRUE]);
  free(coin[JFALSE]);
  free(coin);
  free(c);

  if ((close(fd)) != 0) {
    die(JTRUE, "File descriptor could not be closed correctly!\n");
  }

  die(JFALSE, NULL);
}

/// vim:ts=4:sts=4:sw=4:et:ai:si:sta:noci:nopi:
