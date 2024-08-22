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
  int fd = -1;

  if ((fd = open(logfile, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0) {
    vdie(1, "File descriptor unavailable (%d)\n", fd);
  }

  if (!args || args == NULL) {
    if (fd > 0) {
      vfdlog(fd, "No arguments given\n");
      close(fd);
    }

    die(1, "No arguments given\n");
  }

  for (uint i = 0; i < (uint)argc - 1; i++) {
    vfdlog(fd, "%s\n", args[i]);
    printf("%s\n", args[i]);
  }

  if (close(fd) < 0) {
    vdie(1, "File descriptor couldn't be closed (%d)\n", fd);
  }

  die(0, NULL);
}

/// vim:ts=2:sts=2:sw=2:et:ai:si:sta:noci:nopi:
