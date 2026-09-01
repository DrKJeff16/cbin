#if !defined(JDIE_H)
#define JDIE_H 1

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include "jtypes.h"

/** \addtogroup libjeff
 * @{
 */

/**
 * \brief Terminate program and optionally print message
 *
 * If exit code is 0 message will be printed to `stdout`. Otherwise it'll be `stderr`
 *
 * \param code Exit code
 * \param msg Output string to print before termination. If `NULL` then no message will be printed
 */
void die(const int code, char *const msg);

/**
 * \brief Terminate program and optionally print formatted string
 *
 * If exit code is 0 message will be printed to `stdout`. Otherwise it'll be `stderr`
 *
 * \param code Exit code
 * \param fmt Formatted string to print before termination. If `NULL` then no message will be
 * printed
 * \param ...
 */
void vdie(const int code, char *const fmt, ...);

/**
 * \brief Conditionally terminate program and optionally print formatted string
 *
 * If exit code is 0 message will be printed to `stdout`. Otherwise it'll be `stderr`
 *
 * \param code Exit code
 * \param cond The boolean-like value that acts as the condition
 * \param msg Output string to print before termination. If `NULL` then no message will be printed
 */
void cond_die(const int code, const jbool cond, char *const msg);

/**
 * \brief Conditionally terminate program and optionally print formatted string
 *
 * If exit code is 0 message will be printed to `stdout`. Otherwise it'll be `stderr`
 *
 * \param code Exit code
 * \param cond The boolean-like value that acts as the condition
 * \param fmt Formatted string to print before termination. If `NULL` then no message will be printed
 * \param ...
 */
void cond_vdie(const int code, const jbool cond, char *const fmt, ...);

/**
 * \brief Terminate program, show ERRNO value, and optionally print formatted string
 *
 * If exit code is 0 message will be printed to `stdout`. Otherwise it'll be `stderr`
 *
 * \param code Exit code
 * \param errno_val The errno code
 * \param msg Output string to print before termination. If `NULL` then no message will be printed
 */
void j_errno_die(const int code, const int errno_val, char *const msg);

/**
 * \brief Terminate program, show ERRNO value execute function and optionally print formatted string.
 *
 * If exit code is 0 message will be printed to `stdout`. Otherwise it'll be `stderr`
 *
 * \param code Exit code
 * \param errno_val The errno code
 * \param fmt Formatted string to print before termination. If `NULL` then no message will be
 * printed
 * \param ...
 */
void j_errno_vdie(const int code, const int errno_val, char *const fmt, ...);

/**
 * \brief Terminate program, execute function and optionally print formatted string
 *
 * If exit code is 0 message will be printed to `stdout`. Otherwise it'll be `stderr`
 *
 * \param code Exit code
 * \param fun Function pointer (**`void`, no args**)
 * \param fmt Formatted string to print before termination. If `NULL` then no message will be
 * printed
 * \param ...
 */
void exec_vdie(const int code, void (*fun)(void), char *const fmt, ...);

/**
 * \brief Show program usage, then terminate execution with given exit code.
 *
 * If exit code is 0 the message will be printed to `stdout`. Otherwise it'll be `stderr`.
 *
 * \param code Exit code
 */
static void usage(const int code);

/** @} */

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* !JDIE_H */

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
