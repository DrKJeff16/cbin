#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <jeff/jeff.h>
#include <jeff/jlog.h>

int fdlog(int fd, const char *msg) {
  if (fd < 0) {
    verr("(fdlog): %s\n", "Invalid file descriptor");
    return -1;
  }

  return write(fd, msg, strnlen(msg, 1024));
}

int log_to_file(const char *path, const J_UULONG buf_max, const char *msg, const jbool need_fd) {
  if (!path || path == NULL) {
    vdie(2, "File path invalid or NULL\n");
  }

  if (msg == NULL) {
    verr("(log_to_file): %s\n", "No message was given to log");
    return -1;
  }

  int logfile_fd = -1;
  if ((logfile_fd = open(path, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR | S_IROTH | S_IRGRP)) <
      0) {
    verr("Unable to write log to `%s`\n", path);
    return -1;
  }

  if (write(logfile_fd, msg, strnlen(msg, buf_max)) < 0) {
    verr("Unable to write log to file: %s\n", path);
    return -1;
  }

  if (need_fd) {
    return logfile_fd;
  }

  int close_d = close(logfile_fd);

  if (close_d < 0) {
    verr("Unable to close file descriptor for `%s` (%d)\n", path, close_d);
    return -1;
  } else {
    return 0;
  }
}

/// vim:ts=4:sts=4:sw=4:et:ai:si:sta:noci:nopi:
