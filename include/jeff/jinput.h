#if !defined(JINPUT_H)
#define JINPUT_H 1

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include <jeff/jtypes.h>
#include <stddef.h>

char *buffer_get(char *const msg, const size_t buf_len);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* !JINPUT_H */

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
