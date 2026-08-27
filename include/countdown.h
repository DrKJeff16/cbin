#if !defined(COUNTDOWN_H)
#define COUNTDOWN_H 1

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include <jeff/jtypes.h>

/**
 * \struct arguments
 */
struct arguments {
  jbool verbose;    ///< Enables verbose mode.
  jbool show;       ///< Shows the countdown in the terminal output.
  jbool flush;      ///< Whether to flush the output of each count or not.
  j_uint duration;  ///< How much does each step should last (default is 1).
  j_uint num;       ///< Specifies where should the countdown start (default is 5).
  size_t n_args;    ///< The number of positional arguments parsed.
  char *sep;        ///< The separator of the printed output (default is `" "`).
  char **args;      ///< The positional arguments array.
};

/**
 * \typedef arg_data
 * \brief The `arguments` struct typedef
 */
typedef struct arguments arg_data;

/**
 * \brief Generate the range from `num` to 0.
 * \param num[in] The starting point.
 * \return The array of steps to be made.
 */
j_uint *gen_range(const j_uint num);

/**
 * \brief Make a countdown
 * \param range[in] Range
 * \param num[in] The number of iterations
 * \param duration[in] The duration of the countdown
 * \param show[in] Whether to show the countdown in the CLI
 * \param flush[in] Whether to flush the printed text
 */
void count_down(const j_uint *const range, const j_uint num, const j_uint duration, const jbool show,
                const jbool flush);

static arg_data init_args(void);

static void verbose_print(const jbool verbose, const char *txt, FILE *restrict stream);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* !COUNTDOWN_H */

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
