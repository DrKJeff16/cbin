#if !defined(JDIE_H)
#define JDIE_H 1

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include <jeff/jtypes.h>

/**
 * @brief Terminate program and optionally print message
 *
 * If exit code is 0 message will be printed to `stdout`. Otherwise it'll be `stderr`
 *
 * @param status Exit code
 * @param msg Output string to print before termination. If `NULL` then no message will be printed
 */
/* ----------------------------------------------------------------------------*/
void die(const int status, char *const msg);

/* ----------------------------------------------------------------------------*/
/**
 * @brief Terminate program and optionally print formatted string
 *
 * If exit code is 0 message will be printed to `stdout`. Otherwise it'll be `stderr`
 *
 * @param status Exit code
 * @param fmt Formatted string to print before termination. If `NULL` then no message will be
 * printed
 * @param ...
 */
/* ----------------------------------------------------------------------------*/
void vdie(const int status, char *const fmt, ...);

void cond_die(const int status, const jbool cond, char *const msg);
void cond_vdie(const int status, const jbool cond, char *const fmt, ...);

void j_errno_die(const int status, const int code, char *const msg);
void j_errno_vdie(const int status, const int errno_val, char *const fmt, ...);

/* ----------------------------------------------------------------------------*/
/**
 * @brief Terminate program, execute function and optionally print formatted string
 *
 * @param status Exit code
 * @param fun Function pointer (**`void`, no args**)
 * @param fmt Formatted string to print before termination. If `NULL` then no message will be
 * printed
 * @param ...
 */
/* ----------------------------------------------------------------------------*/
void exec_vdie(const int status, void (*fun)(void), char *const fmt, ...);

static void usage(const int code);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* !JDIE_H */

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
