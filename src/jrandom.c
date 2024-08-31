#include <fcntl.h>
#include <unistd.h>
#include <jeff/jeff.h>
#include <jeff/jrandom.h>

J_ULLONG fd_urand(const J_ULLONG min, const J_ULLONG max) {
  int fd = open("/dev/urandom", O_RDONLY);

  if (fd < 0) {
    verr("`/dev/urandom` inaccessible (%d)\n", fd);
    return 0;
  }

  J_ULLONG result = 0;

  int read_d = read(fd, &result, sizeof(result));

  if (read_d < 0) {
    err("(fd_urand): Failed to read into buffer\n", NULL);
    close(fd);
    return 0;
  }

  close(fd);

  return JCAST(J_ULLONG, result % (max - min + 1) + min);
}

/// vim:ts=2:sts=2:sw=2:et:ai:si:sta:noci:nopi:
