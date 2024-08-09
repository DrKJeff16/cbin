#ifndef JEFF_H
#error "Header `jeff.h` must be included first"
#endif /* !JEFF_H */

#ifndef JMISC_H
#define JMISC_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <sys/types.h>

int fd_open(char *filename);
void fd_close(int fd);

static char **filter_argv(const uint argc, char **argv);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !JMISC_H */
