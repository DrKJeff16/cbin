#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <jeff/jeff.h>
#include <jeff/jmisc.h>

extern const char logfile[9];

static int log_open(void) {
  return open(logfile, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
}

int main(int argc, char **argv) {
  int *fd = MALLOC(int);

  *fd = log_open();

  if (*fd < 1) {
    free(fd);
    j_errno_vdie(1, EBADFD, "(jmisc): %s\n", "File descriptor could not be opened");
  }

  char **args = filter_argv(JCAST(size_t, argc), argv);

  if (null_ptr(args)) {
    vfdlog(*fd, "(jmisc): %s\n%s\n", strerror(ENOKEY), "No arguments given");
    close(*fd);

    free(fd);
    vdie(1, "(jmisc): %s\n%s\n", strerror(ENOKEY), "No arguments given");
  }

  for (size_t i = 0; i < JCAST(size_t, argc - 1); i++) {
    char *arg = CALLOC(char, strlen(args[i]) + 1);
    stpcpy(arg, args[i]);

    /* capitalize(arg, NULL); */
    char *ddp = dedup_str(arg);

    if (null_ptr(ddp)) {
      vfdlog(*fd, "%s\n", arg);
      printf("%s\n", arg);
    } else {
      vfdlog(*fd, "%s\n", ddp);
      printf("%s\n", ddp);
      free(ddp);
    }

    free(arg);
  }

  free(args);

  int close_d = close(*fd);
  free(fd);

  if (close_d < 0) {
    j_errno_vdie(1, EIO, "(jmisc): %s (%d)\n", "File descriptor couldn't be closed", close_d);
  }

  die(0, NULL);
}

/// vim:ts=2:sts=2:sw=2:et:ai:si:sta:
