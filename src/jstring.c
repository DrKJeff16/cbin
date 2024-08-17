#include <stdlib.h>
#include <string.h>
#include <jeff/jeff.h>
#include <jeff/jstring.h>

jbool compare_two_strings(const char *s1, const char *s2) {
  size_t n = strnlen(s1, 256);

  if (n != strnlen(s2, 256)) {
    return JFALSE;
  }

  for (size_t i = 0; i < n - 1; i++) {
    if (s1[i] != s2[i]) {
      return JFALSE;
    }
  }

  return JTRUE;
}

jbool compare_strv(const char **argv, const size_t len) {
  if (len < 2) {
    err(NULL, "`argv` must be of length 2 or greater");
    return JFALSE;
  }
  if (argv == NULL) {
    err(NULL, "`argv`is NULL");
    return JFALSE;
  }

  for (size_t i = 1; i < len - 1; i++) {
    if (!compare_two_strings(argv[0], argv[i])) {
      return JFALSE;
    }
  }

  return JTRUE;
}
