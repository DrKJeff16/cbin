#if !defined(SHRUG_H)
#define SHRUG_H 1

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include <jeff/jtypes.h>

#define TO_ZERO(zero, str) \
  if (zero) {              \
    printf("%s", str);     \
    fflush(stdout);        \
  } else {                 \
    printf("%s\n", str);   \
  }

struct arguments {
  jbool list;
  jbool zero;
  jbool md;
  jbool random;
  size_t n_args;
  char **args;
};

typedef struct arguments arg_data_t;

const size_t N_EMOTIONS = 19;

enum emotions_index {
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
};

typedef enum emotions_index emotions_idx;

char *emotions(const jbool list, const jbool md, const emotions_idx idx);
jbool is_emotion(char *const arg);
emotions_idx map_emotion(char *const str);
void list_emotions(void);

static arg_data_t init_args(void);
static void show_usage(const int code, arg_data_t *arguments);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* !SHRUG_H */

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
