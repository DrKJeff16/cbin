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

typedef struct _char_ptrs {
  const char *s1;
  const char *s2;
} char_ptrs;

typedef enum _jbool {
  JFALSE = 0,
  JTRUE = 1,
} jbool;

typedef struct _jstate_rel {
  char input;
  j_uint idx;
} jstate_rel;

typedef enum __jlua_type {
  JLUA_NIL = 0,
  JLUA_BOOL,
  JLUA_NUM,
  JLUA_LSTR,
  JLUA_STR,
} jlua_type;

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* !JTYPES_H */

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
