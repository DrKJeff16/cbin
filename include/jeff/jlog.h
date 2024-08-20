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

int fdlog(int fd, const char *msg);
int log_to_file(const char *path, const unsigned long long buf_max, const char *msg,
                const jbool need_fd);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !JLOG_H */

/// vim:ts=2:sts=2:sw=2:et:ai:si:sta:noci:noet:
