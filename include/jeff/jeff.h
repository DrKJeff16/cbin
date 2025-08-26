#if !defined(JEFF_H)
#define JEFF_H 1

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include <jeff/jtypes.h>
#include <jeff/jmemory.h>
#include <jeff/jstring.h>

#include <jeff/jautomata.h>
#include <jeff/jinput.h>
#include <jeff/jlog.h>
#include <jeff/jlua.h>
#include <jeff/jrandom.h>

#define JCAST(type, data) (type)(data)
#define null_ptr(ptr) (!ptr || ptr == NULL)

#define J_PI_F 3.14159265358979323846
#define J_PI_LF 3.1415926535897932384626433832795028841971693993

#define J_TAU_F (2.0F * J_PI_F)
#define J_TAU_LF (2.0L * J_PI_LF)

#define jxor(x, y) (x ^ y)

#define output(status) status ? stderr : stdout

/* ---------------------------------- jerr ------------------------------------*/

/* ----------------------------------------------------------------------------*/
/**
 * @brief Print message to `stderr`
 *
 * @param fmt Format string; if `NULL`, defaults to `"%s\n"`
 * @param msg Message string
 */
/* ----------------------------------------------------------------------------*/
void j_err(char *const fmt, char *const msg);

/* ----------------------------------------------------------------------------*/
/**
 * @brief Print formatted string and variable args to `stderr`
 *
 * @param fmt Format string; if `NULL`, function terminates
 * @param ...
 */
/* ----------------------------------------------------------------------------*/
void j_verr(char *const fmt, ...);

void j_errno_err(const int code, char *const fmt, char *const msg);
void j_errno_verr(const int code, char *const fmt, ...);

/* ----------------------------------------------------------------------------*/
/**
 * @brief Print error message and execute function pointer
 *
 * @param fun Function pointer (**`void`, no args**)
 * @param fmt Format string. If `NULL` then only `fun` executes and then returns
 * @param ...
 */
/* ----------------------------------------------------------------------------*/
void j_exec_verr(void (*fun)(void), char *const fmt, ...);

/* ---------------------------------- jdie ------------------------------------*/

/* ----------------------------------------------------------------------------*/
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

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* !JEFF_H */

/// vim:ts=2:sts=2:sw=2:et:ai:si:sta:noci:nopi:
