#if !defined(JMISC_H)
#define JMISC_H 1

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include <jeff/jtypes.h>

#if !defined(J_STRMATCH)
#define J_STRMATCH(s1, s2) strcmp(s1, s2) == 0
#endif /* !STR_MATCH */

/** \defgroup jmisc All elements from jmisc
 * @{
 */

/**
 * \struct config
 */
struct config {
  char *gf;
  char *name;
  int version;
};

/**
 * \struct jmisc_args
 */
struct jmisc_args {
  char **args;
  size_t n_args;
};

/**
 * \typedef config_t
 * \brief Sample config struct for libinih tests
 */
typedef struct config config_t;

/**
 * \typedef jmisc_arg_t
 * \brief Argument data structure
 */
typedef struct jmisc_args jmisc_arg_t;

/**
 * \brief Parse the options using argp
 * \param key The key or character to parse
 * \param arg The argument that either follows an option, or positional argument. Can be `NULL`
 * \param state The state struct
 * \return Any error value or none in case of parsing failure
 */
static error_t parse_opt(int key, char *arg, argp_state_t *state);

/**
 * \brief Initializes the `jmisc_arg_t` struct
 * \return The `jmisc_arg_t` struct pointer (heap)
 */
static jmisc_arg_t *init_args(void);

/**
 * \brief Handler for libinih parsing
 * \param user Void pointer to parse
 * \param section The INI section name
 * \param key The INI variable key
 * \param value The INI variable value
 */
static int j_ini_handler(void *user, const char *section, const char *key, const char *value);

/** @} */

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* !JMISC_H */

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
