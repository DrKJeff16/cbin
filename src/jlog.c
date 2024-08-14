#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <jeff/jeff.h>
#include <jeff/jmemory.h>
#include <jeff/jstring.h>
#include <jeff/jlog.h>

extern int errno;

int log_to_file(const char *path, size_t n, const char *msg, const jbool need_fd) {
  if (msg == NULL) {
    err(NULL, "No message was given to log");
    return -1;
  }

  int logfile_fd = -1;
  if ((logfile_fd = open(path, O_RDWR)) < 0) {
    err("Unable to write log to file: %s\n", path);
    return -1;
  }

  if (write(logfile_fd, msg, n) < 0) {
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
