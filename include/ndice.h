#if !defined(DICE_H)
#define DICE_H 1

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include <jeff/jtypes.h>

/**
 * @struct arguments
 */
struct arguments {
  jbool urandom;      ///< Toggles the usage of `/dev/urandom` instead of `/dev/random`.
  jbool single;       ///< Signals whether a single throw should be performed.
  j_ullong n_throws;  ///< The amount of throws to perform.
  size_t n_args;      ///< The number of positional arguments.
  char **args;        ///< An array of strings.
};

/**
 * @brief The typedef for the `arguments` struct.
 */
typedef struct arguments arg_data;

struct ndice {
  j_ullong idx;
  j_ullong n_landings;
  char *value;
  struct ndice *prev;
  struct ndice *next;
};

typedef struct ndice ndice_t;

static void seed_dice(void);

ndice_t *new_ndice(ndice_t *const main_ndice, char *const value);
ndice_t *gen_full_ndice(char *const values);

ndice_t *ndice_start(ndice_t *const ndice);
ndice_t *ndice_end(ndice_t *const ndice);
ndice_t *ndice_index(ndice_t *const ndice, const size_t index);
ndice_t *ndice_next(ndice_t *const ndice);
ndice_t *ndice_prev(ndice_t *const ndice);

size_t ndice_len(ndice_t *const ndice);

ndice_t *ndice_pop(ndice_t *ndice);
void ndice_insert(ndice_t *ndice, ndice_t *const new_ndice, const size_t index);
void ndice_append(ndice_t *ndice, ndice_t *const new_ndice);

void ndice_reset_count(ndice_t *ndice);
void ndice_wipe(ndice_t *ndice);

void ndice_throw(ndice_t *ndice, const jbool urandom);

/**
 * @brief Initialize the `arg_data` struct with the default values.
 * @return The `arguments` struct type.
 */
static arg_data init_args(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* !DICE_H */

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
