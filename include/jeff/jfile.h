#if !defined(JFILE_H)
#define JFILE_H 1

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include "jtypes.h"

/** \addtogroup libjeff
 * @{
 */

/**
 * \brief Check if given path string is a file
 * \param path The file path string
 * \return Boolean-like that indicates if said file exists
 */
jbool is_file(const char *restrict path);

/** @} */

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* !JFILE_H */

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
