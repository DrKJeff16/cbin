#if !defined(JRANDOM_H)
#define JRANDOM_H 1

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include "jtypes.h"

j_ullong fd_urand(int fd, const j_ullong min, const j_ullong max);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* !JRANDOM_H */

/// vim:ts=4:sts=4:sw=4:et:ai:si:sta:noci:nopi:
