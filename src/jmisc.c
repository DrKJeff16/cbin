#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <jeff/jeff.h>
#include <jeff/jlog.h>
#include <jeff/jstring.h>
#include <jeff/jmisc.h>

const char logfile[9] = "misc.log";

int main(int argc, char **argv) {
  int fd = open(logfile, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

  if (fd < 0) {
    vdie(1, "File descriptor unavailable (%d)\n", fd);
  }

  char **args = filter_argv((size_t)argc, argv);

  if (null_ptr(args)) {
    fdlog(fd, "No arguments given");
    close(fd);

    free(args);
    die(1, "No arguments given");
  }

  for (size_t i = 0; i < (size_t)argc - 1; i++) {
    vfdlog(fd, "%s\n", args[i]);
    printf("%s\n", args[i]);
  }

  int close_d = close(fd);
  if (close_d < 0) {
    free(args);
    vdie(1, "File descriptor couldn't be closed (%d)\n", close_d);
  }

  free(args);
  die(0, NULL);
}

/// vim:ts=2:sts=2:sw=2:et:ai:si:sta:noci:nopi:
