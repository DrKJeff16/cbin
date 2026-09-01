#if !defined(JRANDOM_H)
#define JRANDOM_H 1

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include "jtypes.h"

/** \addtogroup libjeff
 * @{
 */

static jbool seeded = JFALSE;

/**
 * \brief Get random unsigned integer values in a range, polled from `/dev/urandom`
 * \param fd The file descriptor for `/dev/urandom`
 * \param min The minimum value of the range
 * \param max The maximum value of the range
 * \return The generated random number
 */
j_ullong fd_urand(const int fd, j_ullong min, j_ullong max);

/**
 * \brief Seed once the random generator, unless forced
 * \param force Whether to force seeding, in case it needs to be done again
 */
void j_seed(const jbool force);

/** @} */

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* !JRANDOM_H */

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
