#if !defined(NWL_TRIM_H)
#define NWL_TRIM_H 1

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include <jeff/jtypes.h>

typedef struct arguments {
  jbool verbose;
  j_ullong keep_lines;
  j_ullong n_files;
  char **files;
} args_t;

jbool is_file(const char *restrict path);
static void files_gc(char **files, const j_ullong n);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* !NWL_TRIM_H */

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
