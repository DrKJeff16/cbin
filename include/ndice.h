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
  jbool verbose;     /*!< Whether verbose mode is enabled or not */
};

/**
 * \struct ndice
 */
struct ndice {
  char *value;         /*!< The value of the element */
  j_ullong idx;        /*!< The index of the dice in the linked list */
  j_ullong n_landings; /*!< The number of landings for this element of the linked list */
  struct ndice *prev;  /*!< The previous element in the linked list */
  struct ndice *next;  /*!< The next element in the linked list */
};

/**
 * \typedef arg_data_t
 * \brief The typedef for the `arguments` struct.
 */
typedef struct arguments arg_data_t;

/**
 * \typedef ndice_t
 * \brief The dice linked list element struct
 */
typedef struct ndice ndice_t;

/**
 * \brief Generate a new dice linked list element
 * \param main_ndice The main dice linked list
 * \param value The value associated to the dice element
 * \return The dice element
 */
ndice_t *new_ndice(ndice_t *const main_ndice, char *const value);

/**
 * \brief Generate a new dice given the supplied string of values
 * \param values The string value of the new element
 * \return The dice linked list element
 */
ndice_t *gen_full_ndice(char *const values);

/**
 * \brief Retrieve the starting element of a dice linked list
 * \param ndice The dice linked list
 * \return The start of the dice, or `NULL` if unavailable
 */
ndice_t *ndice_start(ndice_t *const ndice);

/**
 * \brief Get the last element of the dice linked list
 * \param ndice The dice linked list
 * \return The end of the dice linked list, or `NULL` if unavailable
 */
ndice_t *ndice_end(ndice_t *const ndice);

/**
 * \brief Retrieve the node from a dice linked list by its index
 * \param ndice The dice linked list
 * \param index The index of the element to be retrieved
 * \return The element of the dice linked list at the given index, or `NULL` if unavailable
 */
ndice_t *ndice_index(ndice_t *const ndice, const size_t index);

/**
 * \brief Get the next element from the current one in a dice linked list, if any
 * \param ndice The dice linked list
 * \return The next element of the linked list relative to the current one,
 *         or `NULL` if unavailable
 */
ndice_t *ndice_next(ndice_t *const ndice);

/**
 * \brief Get the previous element from the current one in a dice linked list, if any
 * \param ndice The dice linked list
 * \return The previous element of the dice linked list relative to the current,
 *         or `NULL` if unavailable
 */
ndice_t *ndice_prev(ndice_t *const ndice);

/**
 * \brief Pop the last value of the dice linked list
 * \param ndice The dice linked list
 * \return The last element of the dice linked list, removed from the original dice,
 *         or `NULL` if unavailable
 */
ndice_t *ndice_pop(ndice_t *ndice);

/**
 * \brief Remove an element from a dice linked list given an index
 * \param ndice The dice linked list
 * \param index The index of the element to remove
 * \return The removed dice linked list element, or `NULL` if unavailable
 */
ndice_t *ndice_remove(ndice_t *ndice, const size_t index);

/**
 * \brief Fix the indeces for each element in a dice linked list
 * \param ndice The dice linked list
 */
void ndice_fix_indeces(ndice_t *ndice);

/**
 * \brief Get the length of a dice linked list
 * \param ndice The dice linked list
 * \return The length of the dice linked list, or `0` if the dice is `NULL`
 */
j_llong ndice_len(ndice_t *const ndice);

/**
 * \brief Insert a new dice element into a dice linked list to a specific index
 * \param ndice The dice linked list
 * \param new_ndice The new single dice element to be inserted
 * \param index The index in which to insert the new dice
 */
void ndice_insert(ndice_t *ndice, ndice_t *const new_ndice, const size_t index);

/**
 * \brief Append a dice element into a dice linked list
 * \param ndice The dice linked list
 * \param new_ndice The new single dice element to be appended
 */
void ndice_append(ndice_t *ndice, ndice_t *const new_ndice);

/**
 * \brief Reset the counters for all the dice linked list elements
 * \param ndice The dice linked list
 */
void ndice_reset_count(ndice_t *ndice);

/**
 * \brief Wipe a dice linked list
 * \param ndice The dice linked list
 */
void ndice_wipe(ndice_t *ndice);

/**
 * \brief Make a "dice throw" for a dice linked list
 * \param ndice The dice linked list
 * \param urandom Whether to use `/dev/urandom` instead of `/dev/random`
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

/**
 * \brief Parse the command arguments
 * \param key The argument or option to be parsed
 * \param arg The positional argument, or the argument for an option, should it support it
 * \param state the `argp_state_t` pointer
 * \return Any error number, or none
 */
static error_t parse_opt(int key, char *arg, argp_state_t *state);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* !DICE_H */

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
