#if !defined(JINPUT_H)
#define JINPUT_H 1

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include <sys/types.h>

char *buffer_get(char *const msg, size_t *const buf_len);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* !JINPUT_H */

/// vim:ts=2:sts=2:sw=2:et:ai:si:sta:
