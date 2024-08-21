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

void write_fd(int *const fd, const char *const fmt, char **const args, const size_t len) {
  if (*fd < 0 || !len || (!args || NULL == args)) {
    return;
  }

  for (uint i = 0; i < len; i++) {
    if ((*fd = vfdlog(*fd, fmt, args[i])) < 0) {
      return;
    }
  }
}

int main(int argc, char **argv) {
  char **args = filter_argv((uint)argc, argv);
  int fd = -11;

  if ((fd = open(logfile, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0) {
    vdie(1, "File descriptor unavailable (%d)\n", fd);
  }

  if (!args || args == NULL) {
    if (fd > 0) {
      fdlog(fd, "No arguments given\n");
      close(fd);
    }

    die(1, "No arguments given");
  }

  for (uint i = 0; i < (uint)argc - 1; i++) {
    fdlog(fd, args[i]);
    fdlog(fd, "\n");

    printf("%s\n", args[i]);
  }

  if (close(fd) < 0) {
    vdie(1, "File descriptor couldn't be closed (%d)\n", fd);
  }

  die(0, NULL);
}

/// vim:ts=4:sts=4:sw=4:et:ai:si:sta:noci:nopi:
