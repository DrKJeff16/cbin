#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <jeff/jeff.h>
#include <jeff/jlog.h>

int fdlog(int fd, char *const msg) {
  if (fd < 0) {
    err("(fdlog): %s\n", "Invalid file descriptor");
    return -1;
  }

  if (!msg || msg == NULL) {
    err("(fdlog): %s\n", "NULL format string");
    return -1;
  }

  return write(fd, msg, strlen(msg) + 1);
}

int vfdlog(int fd, char *const fmt, ...) {
  if (fd < 0) {
    err("(vfdlog): %s\n", "Invalid file descriptor");
    return -1;
  }

  if (!fmt || fmt == NULL) {
    err("(vfdlog): %s\n", "NULL format string");
    return -1;
  }

  va_list argp;
  va_start(argp, fmt);
  int res = vdprintf(fd, fmt, argp);
  va_end(argp);

  return res;
}

int log_to_file(const char *path, const J_ULLONG buf_max, char *const msg, const jbool need_fd) {
  if (!path || path == NULL) {
    vdie(2, "(log_to_file): %s\n", "File path points to NULL");
  }

  if (!msg || msg == NULL) {
    verr("(log_to_file): %s\n", "No message was given to log");
    return -1;
  }

  int logfile_fd = -1;
  if ((logfile_fd = open(path, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR | S_IROTH | S_IRGRP)) <
      0) {
    verr("(log_to_file): Unable to open `%s`\n", path);
    return -1;
  }

  if (write(logfile_fd, msg, strlen(msg) + 1) < 0) {
    verr("(log_to_file): Unable to write log to file: %s\n", path);
    close(logfile_fd);
    return -1;
  }

  if (need_fd) {
    return logfile_fd;
  }

  int close_d = close(logfile_fd);

  if (close_d < 0) {
    verr("(log_to_file): Unable to close file descriptor for `%s` (%d)\n", path, close_d);
    return -1;
  }

  return 0;
}

/// vim:ts=2:sts=2:sw=2:et:ai:si:sta:noci:nopi:
