#if !defined(NWL_TRIM_H)
#define NWL_TRIM_H 1

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include <jeff/jtypes.h>

/** \defgroup nwl_trim All elements from nwl_trim
 * @{
 */

/**
 * \struct nwltrim_args
 */
struct nwltrim_args {
  char **files;        /*!< The filenames string array */
  j_ullong keep_lines; /*!< How many empty lines to be kept */
  j_ullong n_files;    /*!< The number of files to operate on */
  jbool verbose;       /*!< Whether verbose mode is enabled */
};

/**
 * \typedef nwltrim_arg_t
 * \brief The arguments data structure for argp.h
 */
typedef struct nwltrim_args nwltrim_arg_t;

/**
 * \brief Garbage collector for the files string array
 * \param files The string array to be freed
 * \param n The length of the string array
 */
static void files_gc(char **files, const j_ullong n);

/**
 * \brief Initialize the `nwltrim_arg_t` struct with the default values.
 * \return The `arguments` struct type.
 */
static nwltrim_arg_t init_args(void);

/** @} */

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* !NWL_TRIM_H */

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
