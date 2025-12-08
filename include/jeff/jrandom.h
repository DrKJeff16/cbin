#if !defined(JRANDOM_H)
#define JRANDOM_H 1

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include "jtypes.h"

static jbool seeded = JFALSE;

j_ullong fd_urand(const int fd, j_ullong min, j_ullong max);
void j_seed(const jbool *const force);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* !JRANDOM_H */

/// vim:ts=2:sts=2:sw=2:et:ai:si:sta:
