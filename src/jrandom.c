#include <fcntl.h>
#include <unistd.h>
#include <jeff/jeff.h>
#include <jeff/jmemory.h>
#include <jeff/jrandom.h>

J_ULLONG fd_rand(const J_ULLONG max, const J_ULLONG min) {
  int fd = open("/dev/urandom", O_RDONLY);

  if (fd < 0) {
    verr("`/dev/urandom` inaccessible (%d)", fd);
    return 0;
  }

  J_ULLONG result = 0;

  if (read(fd, &result, sizeof(result)) < 0) {
    close(fd);
    return 0;
  }

  close(fd);

  return (J_ULLONG)(result % (max - min + 1) + min);
}
