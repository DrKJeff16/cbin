#ifndef JMISC_H
#define JMISC_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <sys/types.h>

void write_fd(int *const fd, const char *const fmt, char **const args, const size_t len);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !JMISC_H */

/// vim:ts=4:sts=4:sw=4:et:ai:si:sta:noci:nopi:
