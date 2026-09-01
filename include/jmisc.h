#if !defined(JMISC_H)
#define JMISC_H 1

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include <jeff/jtypes.h>

/**
 * \struct arguments
 */
struct arguments {
  char **args;
  size_t n_args;
};

/**
 * \typedef arg_data_t
 * \brief Argument data structure
 */
typedef struct arguments arg_data_t;

/**
 * \brief Parse the provided INI file
 * \param file_name The path to the INI file
 */
void ini_file_get(char *const file_name);

/**
 * \brief Parse the options using argp
 * \param key The key or character to parse
 * \param arg The argument that either follows an option, or positional argument. Can be `NULL`
 * \param state The state struct
 * \return Any error value or none in case of parsing failure
 */
static error_t parse_opt(int key, char *arg, argp_state_t *state);

/**
 * \brief Initializes the `arg_data_t` struct
 * \return The `arg_data_t` struct
 */
static arg_data_t init_args(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* !JMISC_H */

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
