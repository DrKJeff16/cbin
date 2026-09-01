#if !defined(DICE_H)
#define DICE_H 1

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include <jeff/jtypes.h>

#define NO_SECTION 0

/**
 * \struct arguments
 */
struct arguments {
  char **args;       /*!< An array of strings */
  size_t n_args;     /*!< The number of positional arguments */
  j_ullong n_throws; /*!< The amount of throws to perform */
  jbool single;      /*!< Signals whether a single throw should be performed */
  jbool urandom;     /*!< Toggles the usage of `/dev/urandom` instead of `/dev/random` */
};

/**
 * \typedef arg_data_t
 * \brief The typedef for the `arguments` struct.
 */
typedef struct arguments arg_data_t;

/**
 * \struct ndice
 */
struct ndice {
  j_ullong idx;
  j_ullong n_landings;
  char *value;
  struct ndice *prev;
  struct ndice *next;
};

/**
 * \typedef ndice_t
 */
typedef struct ndice ndice_t;

/**
 * \brief Generate a new dice given the supplied string of values
 * \param values The string value of the new element
 * \return The dice element
 */
ndice_t *gen_full_ndice(char *const values);

/**
 * \param ndice The dice struct
 * \return The start of the dice, or `NULL` if unavailable
 */
ndice_t *ndice_start(ndice_t *const ndice);

/**
 * \param ndice The dice struct
 * \return The end of the dice, or `NULL` if unavailable
 */
ndice_t *ndice_end(ndice_t *const ndice);

/**
 * \param ndice The dice struct
 * \param index The index to get
 * \return The element of the dice at the given index, or `NULL` if unavailable
 */
ndice_t *ndice_index(ndice_t *const ndice, const size_t index);

/**
 * \param ndice The dice struct
 * \return The next element of the dice relative to the current one from the pointer,
 *         or `NULL` if unavailable
 */
ndice_t *ndice_next(ndice_t *const ndice);

/**
 * \param ndice The dice struct
 * \return The previous element of the dice relative to the current one from the pointer,
 *         or `NULL` if unavailable
 */
ndice_t *ndice_prev(ndice_t *const ndice);

/**
 * \param ndice The dice struct
 * \return The last element of the dice, removed from the original dice, or `NULL` if unavailable
 */
ndice_t *ndice_pop(ndice_t *ndice);

/**
 * \param ndice The dice struct
 * \param index The index to remove
 * \return The element of the dice specified by the given index, removed from the original dice,
 *         or `NULL` if unvailable
 */
void ndice_remove(ndice_t *ndice, const size_t index);

/**
 * \param ndice The dice struct
 * \return The length of the dice, or `0` if the dice is `NULL`
 */
size_t ndice_len(ndice_t *const ndice);

/**
 * \param ndice The dice struct
 * \param new_ndice The new single dice struct to be inserted
 * \param index The index in which to insert the new dice
 */
void ndice_insert(ndice_t *ndice, ndice_t *const new_ndice, const size_t index);

/**
 * \param ndice The dice struct
 * \param new_ndice The new single dice struct to be appended
 */
void ndice_append(ndice_t *ndice, ndice_t *const new_ndice);

/**
 * \param ndice The dice struct
 */
void ndice_reset_count(ndice_t *ndice);

/**
 * \param ndice The dice struct
 */
void ndice_wipe(ndice_t *ndice);

/**
 * \param ndice The dice struct
 * \param urandom Whether to use /dev/urandom instead of /dev/random
 */
void ndice_throw(ndice_t *ndice, const jbool urandom);

/**
 * \brief Initialize the `arg_data_t` struct with the default values.
 * \return The `arguments` struct type.
 */
static arg_data_t init_args(void);

/**
 * \brief Seed the dice
 */
static void seed_dice(void);

static error_t parse_opt(int key, char *arg, argp_state_t *state);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* !DICE_H */

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
