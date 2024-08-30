#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jeff/jeff.h>
#include <jeff/jmemory.h>
#include <jeff/jstring.h>

void str_append_nul(char *str) {
  if (null_ptr(str)) {
    str = MALLOC(char);
    *str = '\0';
    return;
  }

  const size_t len = strlen(str) + 1;
  char *str_og = CALLOC(char, len);
  char *new_str = CALLOC(char, len + 1);

  if (!null_ptr(strchr(str, 0))) {
    return;
  }

  /// If no NUL char in `str`
  if (null_ptr(stpcpy(new_str, str))) {
    new_str[len] = '\0';
  } else {
    new_str = REALLOC(new_str, char, len);
  }

  if (null_ptr(stpcpy(str, new_str))) {
    stpcpy(str, str_og);

    free(new_str);
    free(str_og);

    verr("(str_append_nul): %s\n", "Unable to copy `new_str` back to `str`");
    return;
  }

  free(new_str);
  free(str_og);
}

jbool is_lower(char *const str) {
  if (null_ptr(str)) {
    return JFALSE;
  }

  jbool res = JTRUE;

  for (size_t i = 0; i < strlen(str) + 1; i++) {
    if (str[i] >= 65 && str[i] <= 90) {
      res = JFALSE;
      break;
    }
  }

  return res;
}
jbool is_upper(char *const str) {
  if (null_ptr(str)) {
    return JFALSE;
  }

  jbool res = JTRUE;

  for (size_t i = 0; i < strlen(str) + 1; i++) {
    if (str[i] >= 97 && str[i] <= 122) {
      res = JFALSE;
      break;
    }
  }

  return res;
}

jbool compare_strv(char **const argv, const size_t len) {
  if (len < 2) {
    verr("`argv` must be of length 2 or greater (%d)\n", len);
    return JFALSE;
  }
  if (null_ptr(argv)) {
    err("%s\n", "`argv`is NULL");
    return JFALSE;
  }

  for (size_t i = 1; i < len - 1; i++) {
    if (!strcmp(argv[0], argv[i])) {
      return JFALSE;
    }
  }

  return JTRUE;
}

char *str_reversed(char *const str) {
  if (null_ptr(str)) {
    return NULL;
  }

  const J_ULLONG len = (J_ULLONG)strlen(str);
  char *result = CALLOC(char, len + 1);

  for (J_ULLONG i = 1; i <= len; i++) {
    result[i - 1] = str[len - i];
  }

  result[len] = '\0';

  return result;
}

char **filter_argv(const size_t argc, char **const argv) {
  size_t len = argc;

  if (len <= 1) {
    return NULL;
  }

  char **result = CALLOC(char *, len - 1);

  for (size_t i = 1; i < len; i++) {
    if (argv[i] != NULL) {
      const size_t i_len = strlen(argv[i]) + 1;
      result[i - 1] = CALLOC(char, i_len);

      if (stpcpy(result[i - 1], argv[i]) == NULL) {
        str_append_nul(result[i - 1]);
      }
    } else {
      free(result[i - 1]);
      result[i - 1] = NULL;
    }
  }

  return result;
}

/// vim:ts=2:sts=2:sw=2:et:ai:si:sta:noci:nopi:
