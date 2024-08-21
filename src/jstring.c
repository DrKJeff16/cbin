#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jeff/jeff.h>
#include <jeff/jmemory.h>
#include <jeff/jstring.h>

void str_append_nul(char *str) {
  char *new_str = NULL;
  const size_t len = strlen(str);

  if (str == NULL) {
    new_str = MALLOC(char);
    *new_str = '\0';
  } else {
    new_str = CALLOC(char, len + 1);

    /// If no NUL char in `str`
    if (stpcpy(new_str, str) == NULL) {
      new_str[len] = '\0';
    } else {
      new_str = REALLOC(new_str, char, len);
    }
  }

  if (stpcpy(str, new_str) == NULL) {
    free(new_str);
    vdie(1, "(str_append_nul): %s\n", "Unable to copy `new_str` back to `str`");
  }

  free(new_str);
}

jbool compare_two_strings(const char *const s1, const char *const s2) {
  size_t n = strlen(s1);

  if (n != strlen(s2)) {
    return JFALSE;
  }

  for (size_t i = 0; i < n - 1; i++) {
    if (s1[i] != s2[i]) {
      return JFALSE;
    }
  }

  return JTRUE;
}

jbool compare_strv(char **const argv, const size_t len) {
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

char **filter_argv(const uint argc, char **const argv) {
  uint len = argc;

  if (len <= 1) {
    return NULL;
  }

  char **const result = CALLOC(char *, len - 1);

  for (uint i = 1; i < len; i++) {
    result[i - 1] = argv[i];
    str_append_nul(result[i - 1]);
  }

  return result;
}

/// vim:ts=4:sts=4:sw=4:et:ai:si:sta:noci:nopi:
