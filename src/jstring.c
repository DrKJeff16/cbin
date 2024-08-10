#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <jeff/jeff.h>
#include <jeff/jmemory.h>
#include <jeff/jstring.h>

jbool compare_two_strings(char *s1, char *s2, const uint n) {
  if (s1 == NULL || s2 == NULL) {
    die(1, "NULL strings cannot be compared");
  }

  jbool status = JTRUE;

  char_ptrs *ogs = MALLOC(char_ptrs);
  ogs->s1 = s1;
  ogs->s2 = s2;

  for (uint i = 0; i < n; i++) {
    if (*s1 != *s2) {
      err("Couldn't compare both strings");
      status = JFALSE;
      break;
    }

    ++s1;
    ++s2;
  }

  /* Restore the original pointers */
  s1 = ogs->s1;
  s2 = ogs->s2;

  free(ogs);

  return status;
}
