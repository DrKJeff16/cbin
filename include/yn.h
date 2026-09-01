#if !defined(YES_NO_H)
#define YES_NO_H 1

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include <jeff/jtypes.h>

/** \defgroup yn All elements from yn
 * @{
 */

#define YN_MAX_EC 300

/**
 * \struct yn_args
 */
struct yn_args {
  char **args;    /*!< The positional arguments passed to the program */
  int code;       /*!< The custom exit code in case of failure */
  jbool invert;   /*!< Whether to invert the exit code when only pressing ENTER */
  size_t n_args;  /*!< The amount of positional arguments passed to the program */
  j_ullong tries; /*!< How many tries before failing */
};

/**
 * \typedef yn_arg_t
 * \brief The arguments struct to be parsed
 */
typedef struct yn_args yn_arg_t;

/**
 * \brief Make a yes/no prompt given the arguments struct
 * \param arguments The `yn_arg_t` struct
 */
void yes_no(yn_arg_t *arguments);

/**
 * \brief Create a prompt preceding the user input
 * \param msg The messages for the prompt
 * \param n The length of the messages array
 * \param negative Whether the default ENTER option is flipped
 */
static void prompt(char **restrict msg, const size_t n, const jbool negative);

/**
 * \brief Garbage collects the arguments struct, then exits with the given code
 * \param arguments The `yn_arg_t` struct
 * \param code The exit code
 */
static void gc_exit(yn_arg_t *arguments, const int code);

/**
 * \brief Initialize the `yn_arg_t` struct
 * \return The `yn_arg_t` struct
 */
static yn_arg_t init_args(void);

/**
 * \brief Signal handler
 * \param sig The signal passed
 */
static void sig_handler(const int sig);

/** @} */

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* !YES_NO_H */

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
