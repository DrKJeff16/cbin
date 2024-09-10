#if !defined(JAUTOMATA_H)
#define JAUTOMATA_H

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include "jeff.h"

typedef struct _jstate_rel {
  char input;
  J_UINT idx;
} jstate_rel;

typedef struct _jstate {
  jstate_rel *transitions;
  jbool FINAL;
  J_UINT idx;
} jstate;

typedef struct _jautomaton {
  char *alphabet;
  J_UINT n_states;
  jstate *states;
  jstate *init_state;
  jstate *final_states;
} jautomaton;

jautomaton *gen_automaton(char *const alpha, const J_UINT n, char **const inputs, J_UINT **const indeces);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* !JAUTOMATA_H */
