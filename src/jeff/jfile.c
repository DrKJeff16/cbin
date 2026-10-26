#include <jeff/jfile.h>
#include <jeff/jmemory.h>
#include <jeff/jtypes.h>
#include <sys/stat.h>

jbool is_file(const char *restrict path) {
  jbool result = JFALSE;
  if (!NULL_PTR(path)) {
    struct stat path_stat;
    stat(path, &path_stat);
    result = S_ISREG(path_stat.st_mode) ? JTRUE : JFALSE;
  }
  return result;
}

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
