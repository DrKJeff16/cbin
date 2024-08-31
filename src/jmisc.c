#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <jeff/jeff.h>
#include <jeff/jmemory.h>
#include <jeff/jlog.h>
#include <jeff/jstring.h>
#include <jeff/jmisc.h>

const char logfile[9] = "misc.log";

static int log_open(void) {
  int fd = open(logfile, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

  if (fd < 0) {
    verr("(log_open): %s\n%s (%d)\n", strerror(EBADFD), "File descriptor unavailable", fd);
  }

  return fd;
}

int main(int argc, char **argv) {
  int *fd = MALLOC(int);

  *fd = log_open();

  if (*fd < 1) {
    free(fd);
    vdie(1, "%s\n", strerror(EBADFD));
  }

  char **args = filter_argv(JCAST(size_t, argc), argv);

  if (null_ptr(args)) {
    vfdlog(*fd, "(jmisc): %s\n%s\n", strerror(ENOKEY), "No arguments given");
    close(*fd);

    free(args);
    free(fd);
    vdie(1, "(jmisc): %s\n%s\n", strerror(ENOKEY), "No arguments given");
  }

  for (size_t i = 0; i < JCAST(size_t, argc - 1); i++) {
    vfdlog(*fd, "%s\n", args[i]);
    printf("%s\n", args[i]);
  }

  int close_d = close(*fd);

  free(fd);
  free(args);
  if (close_d < 0) {
    vdie(1, "(jmisc): %s\n%s (%d)\n", strerror(EIO), "File descriptor couldn't be closed", close_d);
  }

  die(0, NULL);
}

/// vim:ts=2:sts=2:sw=2:et:ai:si:sta:noci:nopi:
