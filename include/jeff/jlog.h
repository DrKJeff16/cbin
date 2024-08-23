#ifndef JLOG_H
#define JLOG_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <sys/types.h>

#include "jeff.h"

typedef enum __j_fdflags {
  OVERWRITE = 0,
  APPEND = 1,
} j_fdflag;

int fdlog(int fd, char *const msg);
int log_to_file(const char *path, const J_UULONG buf_max, char *const msg, const jbool need_fd);
int vfdlog(int fd, char *const fmt, ...);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !JLOG_H */

/// vim:ts=4:sts=4:sw=4:et:ai:si:sta:noci:nopi:
