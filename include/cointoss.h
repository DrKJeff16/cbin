#if !defined(COINTOSS_H)
#define COINTOSS_H 1

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include <jeff/jtypes.h>

/** \defgroup cointoss All elements from cointoss
 * @{
 */

/**
 * \struct cointoss_args
 */
struct cointoss_args {
  char *args[2];      /*!< A 2-sized array of strings */
  jbool by_exit_code; /*!< Whether to exit the program with an exit code based on the cointoss result */
  size_t count;       /*!< The amount of coins to toss */
  size_t n_args;      /*!< The number of positional arguments */
  j_ullong rep;       /*!< The number of times to "toss the coin" in a single cycle */
  jbool total;        /*!< Whether the total number of runs should be printed */
  jbool urandom;      /*!< Toggles the usage of `/dev/urandom` instead of `/dev/random` */
  jbool verbose;      /*!< Enables verbose mode if set to `JTRUE` */
};

enum cointoss_values {
  HEADS = JFALSE,
  TAILS = JTRUE,
};

/**
 * \typedef cointoss_value_t
 * \brief The enum value types for each coin's element index
 */
typedef enum cointoss_values cointoss_value_t;

/**
 * \typedef cointoss_arg_t
 * \brief The typedef for the `arguments` struct
 */
typedef struct cointoss_args cointoss_arg_t;

/**
 * \brief The amount of times a random toss is made given the file descriptor
 * \param args The arguments struct
 * \return Whether the coin tossed to "heads" (0) or "tails" (1)
 */
cointoss_value_t fd_toss(cointoss_arg_t *args);

/**
 * \brief Initialize the coin choices pointer
 * \return The coin pointer, heap-array
 */
j_ullong *init_coin(void);

/**
 * \brief With the given `result` increment the corresponding coin array
 * \param result Either 0 ("heads") or 1 ("tails")
 * \param c The coin array
 */
void decide(const cointoss_value_t result, j_ullong *c);

/**
 * \brief Return the index of the coin array with the largest value.
 * If they're equal, toss the coin again.
 * \param args The arguments struct pointer
 * \param coin The coin array
 * \return Either 0 (HEADS) or 1 (TAILS)
 */
cointoss_value_t cointoss_max_coin(cointoss_arg_t *args, j_ullong *coin);

/**
 * \brief After multiple runs decide what side of the given coin will be printed
 * \param args The arguments struct
 * \param coin The coin array
 * \param choices The 2-sized string array with the text for either coin side
 * \param total The string array with all the total results for each run
 * \param n The size of `total`
 */
void verdict(cointoss_arg_t *args, j_ullong *const coin, char *choices[2], char **total, const size_t n);

/**
 * \brief Print each string from the total strings array
 * \param arguments The arguments struct pointer
 * \param total The string array with all the total results for each run
 * \param n The size of `total`
 */
void show_total(cointoss_arg_t *arguments, cointoss_value_t *ec, char **const total, const size_t n);

/**
 * \brief Initialize the `cointoss_arg_t` struct with the default values
 * \return The `cointoss_arg_t` struct
 */
static cointoss_arg_t init_args(void);

/** @} */

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* !COINTOSS_H */

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
