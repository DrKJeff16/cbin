#if !defined(COINTOSS_H)
#define COINTOSS_H 1

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include <jeff/jtypes.h>

/**
 * \struct arguments
 */
struct arguments {
  jbool urandom;  ///< Toggles the usage of `/dev/urandom` instead of `/dev/random`.
  jbool total;    ///< Whether the total number of runs should be printed.
  jbool verbose;  ///< Enables verbose mode if set to `JTRUE`.
  j_ullong rep;   ///< The number of times to "toss the coin" in a single cycle.
  size_t n_args;  ///< The number of positional arguments.
  size_t count;   ///< The amount of coins to toss.
  char *args[2];  ///< A 2-sized array of strings.
};

/**
 * \brief The typedef for the `arguments` struct.
 */
typedef struct arguments arg_data;

/**
 * \struct coin
 */
struct coin {
  j_ullong TAILS;  ///< The amount of times the "coin" lands on "tails"
  j_ullong HEADS;  ///< The amount of times the "coin" lands on "heads"
};

/**
 * \brief The typedef for the `coin` struct.
 */
typedef struct coin coin_t;

/**
 * \brief The amount of times a random toss is made given the file descriptor.
 * \param fd[in] The file descriptor pointing to either `/dev/random` or `/dev/urandom`.
 * \return Whether the coin tossed to "heads" (0) or "tails" (1).
 */
jbool fd_toss(const int fd);

/**
 * \brief Initialize the coin choices pointer.
 * \return The `coin_t` type pointer (heap).
 */
coin_t *init_coin(void);

/**
 * \brief With the given `result` increment the corresponding `coin_t` struct element.
 * \param result[in] Either 0 ("heads") or 1 ("tails").
 * \param c[in] The `coin` struct pointer.
 */
void decide(const jbool result, coin_t *c);

/**
 * \brief After multiple runs decide what side of the given coin will be printed.
 * \param fd[in] The random file descriptor.
 * \param coin[in] The coin struct pointer.
 * \param choices[in] The 2-sized string array with the text for either coin side.
 * \param total[in] The string array with all the total results for each run.
 * \param n[in] The size of `total`.
 */
void verdict(const int fd, coin_t *coin, char *choices[2], char **total, const size_t n);

/**
 * \brief Print each string from the total strings array.
 * \param choices[in] The 2-sized string array with the text for either coin side.
 * \param total[in] The string array with all the total results for each run.
 * \param n[in] The size of `total`.
 */
void show_total(char *choices[2], char **total, size_t n);

/**
 * \brief Initialize the `arg_data` struct with the default values.
 * \return The `arguments` struct type.
 */
static arg_data init_args(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* !COINTOSS_H */

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
