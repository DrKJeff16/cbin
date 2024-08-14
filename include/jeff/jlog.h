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

int log_to_file(const char *path, size_t n, const char *msg, const jbool need_fd);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !JLOG_H */
