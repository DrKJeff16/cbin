#if !defined(COUNTDOWN_H)
#define COUNTDOWN_H 1

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include <jeff/jtypes.h>

/** \defgroup countdown All elements from countdown
 * @{
 */

/**
 * \struct countdown_args
 */
struct countdown_args {
  char **args;     /*!< The positional arguments array */
  j_uint duration; /*!< How much does each step should last (default is 1) */
  jbool flush;     /*!< Whether to flush the output of each count or not */
  size_t n_args;   /*!< The number of positional arguments parsed */
  j_uint num;      /*!< Specifies where should the countdown start (default is 5) */
  char *sep;       /*!< The separator of the printed output (default is `" "`) */
  jbool show;      /*!< Shows the countdown in the terminal output */
  jbool verbose;   /*!< Enables verbose mode */
};

/**
 * \typedef countdown_arg_t
 * \brief The `arguments` struct typedef
 */
typedef struct countdown_args countdown_arg_t;

/**
 * \brief Generate the range from `num` to 0
 * \param num The starting point
 * \return The array of steps to be made
 */
j_uint *gen_range(const j_uint num);

/**
 * \brief Make a countdown
 * \param range Range
 * \param num The number of iterations
 * \param duration The duration of the countdown
 * \param show Whether to show the countdown in the CLI
 * \param flush Whether to flush the printed text
 */
void count_down(const j_uint *const range, const j_uint num, const j_uint duration, const jbool show,
                const jbool flush);

/**
 * \brief Initialize `countdown_arg_t` arguments for a program
 * \return The `countdown_arg_t` struct
 */
static countdown_arg_t init_args(void);

/**
 * \brief Only print if `verbose` is enabled
 * \param verbose Whether verbose is enabled
 * \param txt The string to print
 * \param stream The output stream. Defaults to `stdout`
 */
static void verbose_print(const jbool verbose, const char *txt, FILE *restrict stream);

/** @} */

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* !COUNTDOWN_H */

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
