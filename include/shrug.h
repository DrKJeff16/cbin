#if !defined(SHRUG_H)
#define SHRUG_H 1

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include <jeff/jtypes.h>

typedef struct arguments {
  jbool list;
  char *args;
} arg_data;

const size_t N_EMOTIONS = 19;

typedef enum emotions_index {
  FACEPALM,
  FIGHT,
  FUCKYOU,
  LENNY,
  LENNYFIGHT,
  LENNYSHRUG,
  LOVE,
  MEH,
  NERD,
  NICE,
  OMG,
  REALLY,
  SADLENNY,
  SHRUG,
  SMILE,
  THIS,
  TY,
  WOO,
  WTF,
} emotions_idx;

static arg_data init_args(void);
char *emotions(const jbool list, const emotions_idx idx);
jbool is_emotion(char *const arg);
emotions_idx map_emotion(char *const str);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* !SHRUG_H */

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
