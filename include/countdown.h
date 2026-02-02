#if !defined(COUNTDOWN_H)
#define COUNTDOWN_H 1

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include <jeff/jtypes.h>

/**
 * @struct arguments
 */
struct arguments {
  jbool verbose;    ///< Enables verbose mode.
  jbool show;       ///< Shows the countdown in the terminal output.
  j_uint duration;  ///< How much does each step should last (default is 1).
  j_uint num;       ///< Specifies where should the countdown start (default is 5).
  size_t n_args;    ///< The number of positional arguments parsed.
  char **msg;       ///< The positional arguments array.
};

/** The `arguments` struct typedef */
typedef struct arguments arg_data;

/**
 * @brief Generate the range from `num` to 0.
 * @param num[in] The starting point.
 * @returns The array of steps to be made.
 */
j_uint *gen_range(const j_uint num);

void count_down(const j_uint *const range, const j_uint num, const j_uint duration, const jbool no_silent);

static arg_data init_args(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* !COUNTDOWN_H */

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
