#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <jeff/jeff.h>
#include <jeff/jlog.h>

extern int errno;

int fdlog(int fd, const char *msg) {
  if (fd < 0) {
    err(NULL, "Invalid file descriptor");
    return -1;
  }

  return write(fd, msg, strnlen(msg, 1024));
}

int log_to_file(const char *path, const unsigned long long buf_max, const char *msg, const jbool need_fd) {
  if (msg == NULL) {
    err(NULL, "No message was given to log");
    return -1;
  }

  int logfile_fd = -1;
  if ((logfile_fd = open(path, O_CREAT | O_RDWR | O_TRUNC,
                               S_IRUSR | S_IWUSR | S_IROTH | S_IRGRP)) < 0) {
    err("Unable to write log to file: %s\n", path);
    return -1;
  }

  if (write(logfile_fd, msg, strnlen(msg, buf_max)) < 0) {
    err("Unable to write log to file: %s\n", path);
    return -1;
  }

  if (need_fd == JTRUE) {
    return logfile_fd;
  } else if (close(logfile_fd) < 0) {
    err("Unable to close file descriptor: %s\n", path);
    return -1;
  } else {
    return 0;
  }
}
