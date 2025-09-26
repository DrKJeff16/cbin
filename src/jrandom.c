#include <errno.h>
#include <unistd.h>
#include <jeff/jeff.h>

j_ullong fd_urand(int fd, const j_ullong min, const j_ullong max) {
  if (fd < 0) {
    j_errno_verr(EBADF, "(fd_urand): %s (fd: %d)\n", "File descriptor inaccessible", fd);
    return 0;
  }

  j_ullong result = 0;

  int read_d = read(fd, &result, sizeof(result));

  if (read_d < 0) {
    j_errno_verr(EIO, "(fd_urand): %s (%d)\n", "Failed to read into buffer", read_d);
    return 0;
  }

  return result % (max - min + 1) + min;
}

/// vim:ts=4:sts=4:sw=4:et:ai:si:sta:
