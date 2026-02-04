#if !defined(JTYPES_H)
#define JTYPES_H 1

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include <argp.h>

typedef unsigned short int j_ushint;
typedef unsigned short j_ushort;
typedef unsigned char j_uchar;
typedef unsigned int j_uint;
typedef unsigned long j_ulong;
typedef unsigned long long j_ullong;
typedef short int j_shint;
typedef long long j_llong;

typedef struct argp argp_t;
typedef struct argp_state argp_state_t;
typedef struct argp_option argp_option_t;

enum jbool {
  JFALSE = 0,
  JTRUE = 1
};
typedef enum jbool jbool;

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* !JTYPES_H */

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
