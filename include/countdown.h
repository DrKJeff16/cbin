#if !defined(COUNTDOWN_H)
#define COUNTDOWN_H 1

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include <jeff/jtypes.h>

typedef struct arguments {
  jbool verbose;
  j_uint duration;
  j_uint num;
} args_t;

j_uint *gen_range(const j_uint num);
void count_down(const j_uint *const range, const j_uint num, const j_uint duration);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* !COUNTDOWN_H */

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
