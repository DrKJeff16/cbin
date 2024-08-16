#include <stdlib.h>
#include <string.h>
#include <jeff/jeff.h>
#include <jeff/jmemory.h>
#include <jeff/jstring.h>

jbool compare_two_strings(char *s1, char *s2) {
  if (s1 == NULL || s2 == NULL) {
    err(NULL, "NULL strings cannot be compared");
    return JFALSE;
  }

  jbool status = JTRUE;
  size_t n = strnlen(s1, 512);

  if (n != strnlen(s2, 512)) {
    err(NULL, "Strings are of different size");
    return JFALSE;
  }

  char_ptrs *ogs = MALLOC(char_ptrs);
  ogs->s1 = s1;
  ogs->s2 = s2;

  for (size_t i = 0; i < n; i++) {
    if (*s1 != *s2) {
      err("Both strings are of different length: %s ", s1);
      err("%s\n", s2);
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

jbool compare_strv(char **argv, const size_t len) {
  if (len < 2) {
    err(NULL, "`argv` must be of length 2 or greater");
    return JFALSE;
  }
  if (argv == NULL) {
    err(NULL, "`argv`is NULL");
    return JFALSE;
  }

  for (size_t i = 1; i < len; i++) {
    if (!compare_two_strings(argv[0], argv[i])) {
      return JFALSE;
    }
  }

  return JTRUE;
}
