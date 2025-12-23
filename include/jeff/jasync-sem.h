/**
 * \file
 * Counting semaphores implemented on async, copied from protothreads.
 * \author
 * Sandro Magi <naasking@gmail.com>
 *
 */

#ifndef JASYNC_SEM_H
#define JASYNC_SEM_H 1

#include "jasync.h"

typedef struct async_sem {
  unsigned int count;
} jasync_sem;

/**
 * Initialize a semaphore
 *
 * This macro initializes a semaphore with a value for the
 * counter. Internally, the semaphores use an "unsigned int" to
 * represent the counter, and therefore the "count" argument should be
 * within range of an unsigned int.
 *
 * \param s (struct pt_sem *) A pointer to the pt_sem struct
 * representing the semaphore
 *
 * \param c (unsigned int) The initial count of the semaphore.
 * \hideinitializer
 */
#define init_sem(s, c) (s)->count = c

/**
 * Wait for a semaphore
 *
 * This macro carries out the "wait" operation on the semaphore. The
 * wait operation causes the protothread to block while the counter is
 * zero. When the counter reaches a value larger than zero, the
 * protothread will continue.
 *
 * \param pt (struct pt *) A pointer to the protothread (struct pt) in
 * which the operation is executed.
 *
 * \param s (struct pt_sem *) A pointer to the pt_sem struct
 * representing the semaphore
 *
 * \hideinitializer
 */
#define await_sem(s)       \
  do {                     \
    await((s)->count > 0); \
    --(s)->count;          \
  } while (0)

/**
 * Signal a semaphore
 *
 * This macro carries out the "signal" operation on the semaphore. The
 * signal operation increments the counter inside the semaphore, which
 * eventually will cause waiting protothreads to continue executing.
 *
 * \param pt (struct pt *) A pointer to the protothread (struct pt) in
 * which the operation is executed.
 *
 * \param s (struct pt_sem *) A pointer to the pt_sem struct
 * representing the semaphore
 *
 * \hideinitializer
 */
#define signal_sem(s) ++(s)->count

#endif /* !JASYNC_SEM_H */

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
