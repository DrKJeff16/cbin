#include <asm-generic/errno.h>
#include <jeff/jeff.h>
#include <jeff/jrandom.h>
#include <time.h>
#include <unistd.h>

void j_seed(const jbool *const force) {
  if (seeded && (null_ptr(force) || !(*force))) {
    return;
  }

  srand(time(NULL));
  seeded = JTRUE;
}

j_ullong fd_urand(const int fd, j_ullong min, j_ullong max) {
  if (fd < 0) {
    j_errno_verr(EBADF, "(fd_urand): %s (fd: %d)\n", "File descriptor inaccessible", fd);
    return 0;
  }

  if (min > max) {
    J_SWAP(min, max);
  }

  j_ullong result = 0;
  int read_d = read(fd, &result, sizeof(result));
  if (read_d < 0) {
    j_errno_verr(EIO, "(fd_urand): %s (%d)\n", "Failed to read into buffer", read_d);
    return 0;
  }

  return result % (max - min + 1) + min;
}

/// vim:ts=2:sts=2:sw=2:et:ai:si:sta:
