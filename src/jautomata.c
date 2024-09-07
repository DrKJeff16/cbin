#include <stdlib.h>
#include <string.h>
#include <jeff/jeff.h>
#include <jeff/jmemory.h>
#include <jeff/jstring.h>
#include <jeff/jautomata.h>

jautomaton *gen_automaton(char *const alpha, const J_UINT n, char **const inputs,
                          J_UINT **const indeces) {
  if (null_ptr(alpha) || null_ptr(inputs) || null_ptr(indeces) || n <= 1) {
    return NULL;
  }

  jautomaton *res = MALLOC(jautomaton);

  size_t alpha_len = strlen(alpha);

  res->alphabet = CALLOC(char, alpha_len + 1);

  char *chr = stpcpy(res->alphabet, alpha);

  if (null_ptr(chr)) {
    free(res->alphabet);
    free(res);
    return NULL;
  }

  res->n_states = n;
  res->final_states = NULL;

  res->states = CALLOC(jstate, res->n_states);
  for (J_UINT i = 0; i < res->n_states; i++) {
    res->states[i].idx = i;
    res->states[i].FINAL = JFALSE;

    res->states[i].transitions = CALLOC(jstate_rel, alpha_len);
    for (J_UINT j = 0; j < alpha_len; j++) {
      res->states[i].transitions[i].idx = indeces[i][j];
      res->states[i].transitions[i].input = inputs[i][j];
    }
  }

  res->init_state = res->states;

  return res;
}

/// vim:ts=2:sts=2:sw=2:et:ai:si:sta:noci:nopi:
