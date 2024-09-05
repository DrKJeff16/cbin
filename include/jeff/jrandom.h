#ifndef JRANDOM_H
#define JRANDOM_H 1

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "jeff.h"

J_ULLONG fd_urand(int fd, const J_ULLONG min, const J_ULLONG max);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !JRANDOM_H */
