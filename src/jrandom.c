#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <jeff/jeff.h>
#include <jeff/jrandom.h>

J_ULLONG fd_urand(int fd, const J_ULLONG min, const J_ULLONG max) {
  if (fd < 0) {
    verr("(fd_urand): %s\n%s (fd: %d)\n", strerror(EBADF), "File descriptor inaccessible", fd);
    return 0;
  }

  J_ULLONG result = 0;

  int read_d = read(fd, &result, sizeof(result));

  if (read_d < 0) {
    verr("(fd_urand): %s\n%s (%d)\n", strerror(EIO), "Failed to read into buffer", read_d);
    return 0;
  }

  return JCAST(J_ULLONG, result % (max - min + 1) + min);
}

/// vim:ts=2:sts=2:sw=2:et:ai:si:sta:noci:nopi:
