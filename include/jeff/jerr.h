#if !defined(JERR_H)
#define JERR_H 1

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/** \addtogroup libjeff
 * @{
 */

/**
 * \brief Print message to `stderr`
 *
 * \param fmt Format string; if `NULL`, defaults to `"%s\n"`
 * \param msg Message string
 */
void j_err(char *const fmt, char *const msg);

/**
 * \brief Print formatted string and variable args to `stderr`
 *
 * \param fmt Format string; if `NULL`, function terminates
 * \param ...
 */
void j_verr(char *const fmt, ...);

void j_errno_err(const int code, char *const fmt, char *const msg);
void j_errno_verr(const int code, char *const fmt, ...);

/**
 * \brief Print error message and execute function pointer
 *
 * \param fun Function pointer (**`void`, no args**)
 * \param fmt Format string. If `NULL` then only `fun` executes and then returns
 * \param ...
 */
/* ----------------------------------------------------------------------------*/
void j_exec_verr(void (*fun)(void), char *const fmt, ...);

/** @} */

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* !JERR_H */

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
