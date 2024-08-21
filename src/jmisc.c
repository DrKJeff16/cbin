#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <jeff/jeff.h>
#include <jeff/jlog.h>
#include <jeff/jmemory.h>
#include <jeff/jstring.h>
#include <jeff/jmisc.h>

const char logfile[9] = "misc.log";

int main(int argc, char **argv) {
  char **args = filter_argv((uint)argc, argv);
  char ***new_args = CALLOC(char **, 2);
  new_args[0] = args;
  new_args[1] = argv;

  new_args[0] = NULL;
  new_args[1] = NULL;

  int fd = 0;

  if ((fd = open(logfile, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0) {
    free(new_args);
    vdie(1, "File descriptor unavailable (%d)\n", fd);
  }

  if (!args || args == NULL) {
    if (fd > 0) {
      fdlog(fd, "No arguments given\n");
      close(fd);
    }

    free(new_args);
    die(1, "No arguments given");
  }

  for (uint i = 0; i < (uint)argc - 1; i++) {
    fdlog(fd, args[i]);
    fdlog(fd, "\n");

    printf("%s\n", args[i]);
  }

  if (close(fd) < 0) {
    free(new_args);
    vdie(1, "File descriptor couldn't be closed (%d)\n", fd);
  }

  free(new_args);
  die(0, NULL);
}

/// vim:ts=2:sts=2:sw=2:et:ai:si:sta:noci:noet:
