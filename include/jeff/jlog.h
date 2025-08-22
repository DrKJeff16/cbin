#if !defined(JLOG_H)
#define JLOG_H 1

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include "jtypes.h"

int fdlog(int fd, char *const msg);
int log_to_file(char *const path, char *const msg, const jbool need_fd);
int vfdlog(int fd, char *const fmt, ...);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* !JLOG_H */

/// vim:ts=2:sts=2:sw=2:et:ai:si:sta:noci:nopi:
