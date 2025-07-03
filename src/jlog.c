#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <jeff/jeff.h>
#include <jeff/jlog.h>

int fdlog(int fd, char *const msg) {
  if (fd < 0) {
    errno_verr(EBADFD, "(fdlog): %s (%d)\n", "Invalid file descriptor", fd);
    return fd;
  }

  if (null_ptr(msg)) {
    errno_verr(EINVAL, "(fdlog): %s\n", "NULL format string");
    return fd;
  }

  return write(fd, msg, strlen(msg) + 1);
}

int vfdlog(int fd, char *const fmt, ...) {
  if (fd < 0) {
    errno_verr(EBADFD, "(vfdlog): %s (%d)\n", "Invalid file descriptor", fd);
    return -1;
  }

  if (null_ptr(fmt)) {
    errno_verr(EINVAL,
               "(vfdlog): %s\n"
               "NULL format string");
    return -1;
  }

  va_list argp;
  va_start(argp, fmt);
  int res = vdprintf(fd, fmt, argp);
  va_end(argp);

  return res;
}

int log_to_file(char *const path, const j_ullong buf_max, char *const msg, const jbool need_fd) {
  if (null_ptr(path)) {
    errno_verr(EINVAL, "(log_to_file): %s\n", "File path points to NULL");
    return -1;
  }

  if (null_ptr(msg)) {
    errno_verr(EINVAL, "(log_to_file): %s\n", "No message was given to log");
    return -1;
  }

  int logfile_fd = open(path, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR | S_IROTH | S_IRGRP);
  if (logfile_fd < 0) {
    errno_verr(ENOENT, "(log_to_file): Unable to open `%s` (fd: %d)\n", path, logfile_fd);
    return -1;
  }

  int write_d = write(logfile_fd, msg, strlen(msg) + 1);

  if (write_d < 0) {
    errno_verr(EIO, "(log_to_file): Unable to write log to file: `%s` (%d)\n", path, write_d);
    close(logfile_fd);
    return -1;
  }

  if (need_fd) {
    return logfile_fd;
  }

  int close_d = close(logfile_fd);

  if (close_d < 0) {
    errno_verr(ENOTTY, "(log_to_file): Unable to close file descriptor for `%s` (%d)\n", path, close_d);
    return -1;
  }

  return 0;
}

/// vim:ts=4:sts=4:sw=4:et:ai:si:sta:noci:nopi:
