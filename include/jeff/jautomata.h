#if !defined(JAUTOMATA_H)
#define JAUTOMATA_H

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include "jtypes.h"

jautomaton *gen_automaton(char *const alpha, const j_uint n, char **const inputs, j_uint **const indeces);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* !JAUTOMATA_H */
