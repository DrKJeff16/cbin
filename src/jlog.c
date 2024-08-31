#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <jeff/jeff.h>
#include <jeff/jlog.h>

int fdlog(int fd, char *const msg) {
  if (fd < 0) {
    verr("(fdlog): %s\n%s (%d)\n", strerror(EBADFD), "Invalid file descriptor", fd);
    return fd;
  }

  if (null_ptr(msg)) {
    verr("(fdlog): %s\n%s\n", strerror(EINVAL), "NULL format string");
    return fd;
  }

  return write(fd, msg, strlen(msg) + 1);
}

int vfdlog(int fd, char *const fmt, ...) {
  if (fd < 0) {
    verr("(vfdlog): %s\n%s (%d)\n", strerror(EBADFD), "Invalid file descriptor", fd);
    return -1;
  }

  if (null_ptr(fmt)) {
    verr("(vfdlog): %s\n%s\n", strerror(EINVAL), "NULL format string");
    return -1;
  }

  va_list argp;
  va_start(argp, fmt);
  int res = vdprintf(fd, fmt, argp);
  va_end(argp);

  return res;
}

int log_to_file(char *const path, const J_ULLONG buf_max, char *const msg, const jbool need_fd) {
  if (null_ptr(path)) {
    verr("(log_to_file): %s\n%s\n", strerror(EINVAL), "File path points to NULL");
    return -1;
  }

  if (null_ptr(msg)) {
    verr("(log_to_file): %s\n%s\n", strerror(EINVAL), "No message was given to log");
    return -1;
  }

  int logfile_fd = open(path, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR | S_IROTH | S_IRGRP);
  if (logfile_fd < 0) {
    verr("(log_to_file): %s\nUnable to open `%s` (fd: %d)\n", strerror(ENOENT), path, logfile_fd);
    return -1;
  }

  int write_d = write(logfile_fd, msg, strlen(msg) + 1);

  if (write_d < 0) {
    verr("(log_to_file): %s\nUnable to write log to file: `%s` (%d)\n", strerror(EIO), path,
         write_d);
    close(logfile_fd);
    return -1;
  }

  if (need_fd) {
    return logfile_fd;
  }

  int close_d = close(logfile_fd);

  if (close_d < 0) {
    verr("(log_to_file): %s\nUnable to close file descriptor for `%s` (%d)\n", strerror(ENOTTY),
         path, close_d);
    return -1;
  }

  return 0;
}

/// vim:ts=2:sts=2:sw=2:et:ai:si:sta:noci:nopi:
