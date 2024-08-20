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

char **filter_argv(const uint argc, char **argv) {
  if (argc <= 1) {
    return NULL;
  }

  char **result = CALLOC(char *, argc - 1);

  for (uint i = 1; i < (uint)argc; i++) {
    result[i - 1] = argv[i];
    str_append_nul(result[i - 1]);
  }

  return result;
}

int main(int argc, char **argv) {
  char **args = filter_argv((uint)argc, argv);

  int fd = open("misc.log", O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

  if (fd < 0) {
    die(1, "File descriptor unavailable");
  }

  if (args == NULL) {
    if (fd > 0) {
      fdlog(fd, "No arguments given\n");
      close(fd);
    }

    die(1, "No arguments given");
  }

  for (uint i = 0; i < (uint)argc - 1; i++) {
    if (!(fd < 0)) {
      fdlog(fd, args[i]);
      fdlog(fd, "\n");
    }

    printf("%s\n", args[i]);
  }

  if (close(fd) < 0) {
    die(1, "File descriptor couldn't be closed");
  }

  die(0, NULL);
}

/// vim:ts=2:sts=2:sw=2:et:ai:si:sta:noci:noet:
