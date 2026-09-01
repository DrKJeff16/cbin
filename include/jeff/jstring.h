#if !defined(JSTRING_H)
#define JSTRING_H 1

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include "jtypes.h"

#if !defined(J_STRMATCH)
#define J_STRMATCH(s1, s2) strcmp(s1, s2) == 0
#endif

/** \addtogroup libjeff
 * @{
 */

/**
 * \brief Check whether a given string starts with a given substring
 * \param str The string value to be checked on
 * \param start The substring to check against the string
 * \return A boolean-like value indicating whether the search was successful or not
 */
jbool str_startswith(char *const str, char *const start);

/**
 * \brief Reverse a given string
 * \param str The string to reverse
 */
void reverse_str(char *str);

/**
 * \brief Return the reverse of a given string
 * \param str The string to reverse
 * \return The reversed string
 */
char *str_reversed(char *const str);

/**
 * \brief Append null terminator to a string if it doesn't have one already
 * \param str The string to check
 */
void str_append_nul(char *str);

/**
 * \brief Remove duplicated chars from a string
 * \param str The string to check
 * \return The deduplicated string, or `NULL` if argument is NULL
 */
char *dedup_str(char *const str);

/**
 * \brief Repeat for a number of times a given string
 *
 * Source - https://stackoverflow.com/a
 * Posted by BLUEPIXY
 * Retrieved 2025-12-05, License - CC BY-SA 3.0
 *
 * \param s The string to repeat
 * \param n The amount of times to repeat
 * \return The repeated string, or `NULL` if invalid
 */
char *str_rep(const char *const s, const size_t n);

/**
 * \brief Check if a character is in a string
 * \param str The string to check
 * \param c The substring to look for
 * \return Whether the substring is in the string
 */
jbool in_str(char *const str, const char *const c);

/**
 * \brief Check if a string is lowercase
 * \param str The string to check
 * \return Whether the string is lowercase or not
 */
jbool is_lower(char *const str);

/**
 * \brief Check if a string is uppercase
 * \param str The string to check
 * \return Whether the string is uppercase or not
 */
jbool is_upper(char *const str);

/**
 * \brief Check if a character is lowercase
 * \param c The character to check
 * \return Whether the character is lowercase or not
 */
jbool is_lower_char(const char c);

/**
 * \brief Check if a character is uppercase
 * \param c The character to check
 * \return Whether the character is uppercase or not
 */
jbool is_upper_char(const char c);

/**
 * \brief Capitalize a given string
 * \param str The string to capitalize
 */
void capitalize(char *str);

/**
 * \brief Convert a given string into a uppercase string
 * \param str The string to modify
 */
void upperize(char *str);

/**
 * \brief Convert a given string into a lowercase string
 * \param str The string to modify
 */
void lowerize(char *str);

/**
 * \brief Perform a left-strip on a string given a character
 * \param c The character to be stripped
 * \param str The string to strig
 */
void j_lstrip(const char c, char *str);

/**
 * \brief Perform a right-strip on a string given a character
 * \param c The character to be stripped
 * \param str The string to strig
 */
void j_rstrip(const char c, char *str);

/**
 * \brief Perform a left-and-right-strip on a string given a character
 * \param c The character to be stripped
 * \param str The string to strig
 */
void j_strip(const char c, char *str);

/** @} */

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* !JSTRING_H */

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
