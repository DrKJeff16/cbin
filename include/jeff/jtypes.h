#if !defined(JTYPES_H)
#define JTYPES_H 1

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include <argp.h>

/** \addtogroup libjeff
 * @{
 */

/**
 * \typedef j_ushint
 * \brief Alias for `unsigned short int`
 */
typedef unsigned short int j_ushint;

/**
 * \typedef j_ushort
 * \brief Alias for `unsigned short`
 */
typedef unsigned short j_ushort;

/**
 * \typedef j_uchar
 * \brief Alias for `unsigned char`
 */
typedef unsigned char j_uchar;

/**
 * \typedef j_uint
 * \brief Alias for `unsigned int`
 */
typedef unsigned int j_uint;

/**
 * \typedef j_ulong
 * \brief Alias for `unsigned long`
 */
typedef unsigned long j_ulong;

/**
 * \typedef j_ullong
 * \brief Alias for `unsigned long long`
 */
typedef unsigned long long j_ullong;

/**
 * \typedef j_shint
 * \brief Alias for `short int`
 */
typedef short int j_shint;

/**
 * \typedef j_llong
 * \brief Alias for `long long`
 */
typedef long long j_llong;

/**
 * \typedef argp_t
 * \brief Alias for `struct argp`
 */
typedef struct argp argp_t;

/**
 * \typedef argp_state_t
 * \brief Alias for `struct argp_state`
 */
typedef struct argp_state argp_state_t;

/**
 * \typedef argp_option_t
 * \brief Alias for `struct argp_option`
 */
typedef struct argp_option argp_option_t;

/**
 * \enum jbool
 * \brief Boolean-like enum
 */
enum jbool {
  JFALSE = 0, /*!< Same as FALSE */
  JTRUE = 1,  /*!< Same as TRUE */
};

/**
 * \typedef jbool
 * \brief Alias for `enum jbool`
 */
typedef enum jbool jbool;

/** @} */

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* !JTYPES_H */

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
