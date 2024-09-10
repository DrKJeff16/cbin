#if !defined(JRANDOM_H)
#define JRANDOM_H 1

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include "jeff.h"

J_ULLONG fd_urand(int fd, const J_ULLONG min, const J_ULLONG max);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* !JRANDOM_H */
