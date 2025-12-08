#if !defined(JTYPES_H)
#define JTYPES_H 1

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include <stddef.h>

#define j_ushint unsigned short int
#define j_ushort unsigned short
#define j_uchar unsigned char
#define j_uint unsigned int
#define j_ulong unsigned long
#define j_ullong unsigned long long
#define j_shint short int
#define j_llong long long

typedef struct _char_ptrs {
  const char *s1;
  const char *s2;
} char_ptrs;

typedef enum _jbool {
#if defined(true) && defined(false)
  JFALSE = false,
  JTRUE = true,
#else
  JFALSE = 0,
  JTRUE = 1,
#endif
} jbool;

typedef struct _jstate_rel {
  char input;
  j_uint idx;
} jstate_rel;

typedef struct _jstate {
  jstate_rel *transitions;
  jbool FINAL;
  j_uint idx;
} jstate;

typedef struct _jautomaton {
  char *alphabet;
  j_uint n_states;
  jstate *states;
  jstate *init_state;
  jstate *final_states;
} jautomaton;

typedef struct _p_flags {
  jbool VERBOSE;
  jbool LIBS;
} p_flags;

typedef struct _k_flags {
  const char VERBOSE[3];
  const char LIBS[3];
} k_flags;

typedef enum __jlua_type {
  JLUA_NIL = 0,
  JLUA_BOOL,
  JLUA_NUM,
  JLUA_STR,
  JLUA_LSTR,
} jlua_type;

typedef enum __jlua_operator {
  NOOP = 0,
  PUSH,
  CHECK_STACK,
} jlua_operator;

typedef struct _jlua_op {
  struct _jlua_op *_prev;
  j_ullong index;
  jlua_operator _operator;
  jlua_type _type;
  void *data;
  struct _jlua_op *_next;
} jlua_op_buf;

typedef enum __j_fdflags {
  OVERWRITE = 0,
  APPEND = 1,
} j_fdflag;

typedef struct _gl_rgba {
  double red;
  double green;
  double blue;
  double alpha;
} rgba_t;

typedef struct _gl_rgb {
  double red;
  double green;
  double blue;
} rgb_t;

typedef struct _gl_init {
  rgba_t *rgba;
  rgb_t *rgb;
} gl_init_t;

typedef enum _point_flag {
  NO_OP = 0,
  TOP,
  RIGHT,
  BOTTOM,
  LEFT,
} direction_flag;

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* !JTYPES_H */

/// vim:ts=2:sts=2:sw=2:et:ai:si:sta:
