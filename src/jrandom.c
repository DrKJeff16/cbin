#include <errno.h>
#include <unistd.h>
#include <jeff/jeff.h>
#include <jeff/jrandom.h>

J_ULLONG fd_urand(int fd, const J_ULLONG min, const J_ULLONG max) {
  if (fd < 0) {
    errno_verr(EBADF, "(fd_urand): %s (fd: %d)\n", "File descriptor inaccessible", fd);
    return 0;
  }

  J_ULLONG result = 0;

  int read_d = read(fd, &result, sizeof(result));

  if (read_d < 0) {
    errno_verr(EIO, "(fd_urand): %s (%d)\n", "Failed to read into buffer", read_d);
    return 0;
  }

  return result % (max - min + 1) + min;
}

/// vim:ts=2:sts=2:sw=2:et:ai:si:sta:noci:nopi:
