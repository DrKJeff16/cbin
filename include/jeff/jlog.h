#ifndef _ERRNO_H
#error "Header `errno.h` must be included first"
#endif /* !_ERRNO_H */

#ifndef JEFF_H
#error "Header `jeff.h` must be included first"
#endif /* !JEFF_H */

#ifndef JSTRING_H
#error "Header `jstring.h` must be included first"
#endif /* !JSTRING_H */

#ifndef JLOG_H
#define JLOG_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <sys/types.h>

typedef enum __j_fdflags {
  APPEND = 1,
  OVERWRITE = 0,
} j_fdflag;

int fdlog(int fd, const char *msg);
int log_to_file(const char *path, const unsigned long long buf_max, const char *msg, const jbool need_fd);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !JLOG_H */
