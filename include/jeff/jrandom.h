#if !defined(JRANDOM_H)
#define JRANDOM_H 1

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include "jtypes.h"

j_ullong fd_urand(const int fd, const j_ullong min, const j_ullong max);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* !JRANDOM_H */

/// vim:ts=2:sts=2:sw=2:et:ai:si:sta:
