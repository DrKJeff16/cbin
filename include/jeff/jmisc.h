#ifndef JMISC_H
#define JMISC_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <sys/types.h>

int fd_open(char *filename);
void fd_close(int fd);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !JMISC_H */

/// vim:ts=4:sts=4:sw=4:et:ai:si:sta:noci:nopi:
