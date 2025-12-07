#include <jeff/jeff.h>
#include <jeff/jstring.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *str_rep(const char *const s, const size_t n) {
  if (null_ptr(s)) {
    return NULL;
  }

  size_t i, count = 0;
  while (s[count] != '\0') {
    ++count;
  }

  char *new_arr = CALLOC(char, (count * n) + 1);
  char *na = new_arr;
  for (i = 0; i < n; ++i) {
    const char *p = s;
    while (*p) {
      *na++ = *p++;
    }
  }
  *na = '\0';
  return new_arr;
}

jbool in_str(char *const str, const char *const c) {
  if (null_ptr(c) || null_ptr(str)) {
    die(3, (null_ptr(c)) ? "NULL char array!\n" : ((null_ptr(str) ? "NULL string!\n" : NULL)));
  }

  char *s = CALLOC(char, strlen(str) + 1);
  stpcpy(s, str);

  for (size_t i = 0; i <= strlen(s); i++) {
    for (size_t j = 0; j < strlen(c); j++) {
      if (s[i] == c[j]) {
        return JTRUE;
      }
    }
  }

  return JFALSE;
}

/// I gave up, so tysm:
/// https://www.quora.com/How-do-I-write-a-C-program-to-remove-duplicates-from-a-string
char *dedup_str(char *const str) {
  j_ulong len = strlen(str);
  char *res = CALLOC(char, len + 1);
  j_ulong j = 0;

  for (j_ulong i = 0; i < len; i++) {
    j_ulong found = 0;
    for (j_ulong k = 0; k < j; k++) {
      if (res[k] == str[i]) {
        found = 1;
        break;
      }
    }
    if (!found) {
      res[j++] = str[i];
    }
  }

  res[j] = '\0';
  res = REALLOC(res, char, j + 1);
  return res;
}

void str_append_nul(char *str) {
  if (null_ptr(str)) {
    return;
  }

  char *chr = strchr(str, 0);
  if (!null_ptr(chr)) {
    return;
  }

  const size_t len = strlen(str) + 1;
  char *str_og = CALLOC(char, len);
  char *new_str = CALLOC(char, len + 1);

  chr = stpcpy(new_str, str);
  /// If no NUL char in `str`
  if (null_ptr(chr)) {
    new_str[len] = '\0';
  } else {
    new_str = REALLOC(new_str, char, len);
  }

  chr = stpcpy(str, new_str);
  if (null_ptr(chr)) {
    stpcpy(str, str_og);

    j_verr("(str_append_nul): %s\n", "Unable to copy `new_str` back to `str`");
  }

  void **garbage = CALLOC(void *, 2);
  garbage[0] = VOID_PTR(new_str);
  garbage[1] = VOID_PTR(str_og);

  j_gc(garbage, 2);
}

jbool is_lower(char *const str) {
  if (null_ptr(str)) {
    return JFALSE;
  }

  for (j_ulong i = 0; i <= strlen(str); i++) {
    if (str[i] >= 'A' && str[i] <= 'Z') {
      return JFALSE;
    }
  }

  return JTRUE;
}

jbool is_upper(char *const str) {
  if (null_ptr(str)) {
    return JFALSE;
  }

  for (size_t i = 0; i <= strlen(str); i++) {
    if (str[i] >= 'a' && str[i] <= 'z') {
      return JFALSE;
    }
  }

  return JTRUE;
}

void lowerize(char *str) {
  if (null_ptr(str)) {
    return;
  }

  for (j_ulong i = 0; i <= strlen(str); i++) {
    char *c = MALLOC(char);
    *c = str[i];
    if (is_upper(c)) {
      str[i] += 32;
    }

    void **garbage = MALLOC(void *);
    *garbage = VOID_PTR(c);
    j_gc(garbage, 1);
  }
}

void upperize(char *str) {
  if (null_ptr(str)) {
    return;
  }

  for (j_ulong i = 0; i <= strlen(str); i++) {
    char *c = MALLOC(char);
    *c = str[i];
    if (is_lower(c)) {
      str[i] -= 32;
    }

    void **garbage = MALLOC(void *);
    *garbage = VOID_PTR(c);
    j_gc(garbage, 1);
  }
}

void capitalize(char *str) {
  if (null_ptr(str)) {
    j_verr("%s\n", "NULL string cannot be capitalized");
    return;
  }

  jbool space = JTRUE;
  char capital_d = 'a' - 'A';

  for (size_t i = 0; i < strlen(str) + 1; i++) {
    if ((str[i] >= 'a' && str[i] <= 'z') && space) {
      str[i] -= capital_d;
      space = JFALSE;
    } else if ((str[i] >= 'A' && str[i] <= 'Z') && !space) {
      str[i] += capital_d;
    } else if ((str[i] >= 'A' && str[i] <= 'Z') && space) {
      space = JFALSE;
    } else if (str[i] == ' ' || str[i] == '\n') {
      space = JTRUE;
    }
  }
}

jbool compare_strv(char **const argv, const size_t len) {
  if (null_ptr(argv)) {
    j_verr("%s\n", "`argv`is NULL");
    return JFALSE;
  }

  if (len < 2) {
    j_verr("`argv` must be of length 2 or greater (%d)\n", len);
    return JFALSE;
  }

  for (size_t i = 1; i < len; i++) {
    if (!strcmp(argv[0], argv[i])) {
      return JFALSE;
    }
  }

  return JTRUE;
}

void reverse_str(char *s) {
  if (null_ptr(s)) {
    return;
  }

  size_t l = 0, r = strlen(s) - 1;

  while (l < r) {
    char t = s[l];
    s[l] = s[r];
    s[r] = t;

    l++;
    r--;
  }
}

char *str_reversed(char *const str) {
  if (null_ptr(str)) {
    return NULL;
  }

  char *new_str = CALLOC(char, strlen(str) + 1);

  if (null_ptr(stpcpy(new_str, str))) {
    return NULL;
  }

  reverse_str(new_str);

  return new_str;
}

char **filter_argv(const size_t argc, char **const argv) {
  size_t len = argc;

  if (len <= 1) {
    return NULL;
  }

  char **result = CALLOC(char *, len - 1);
  char *chr = NULL;

  for (size_t i = 1; i < len; i++) {
    if (!null_ptr(argv[i])) {
      const size_t i_len = strlen(argv[i]) + 1;
      result[i - 1] = CALLOC(char, i_len);

      chr = stpcpy(result[i - 1], argv[i]);

      if (null_ptr(chr)) {
        str_append_nul(result[i - 1]);
      }
    } else {
      result[i - 1] = NULL;
    }
  }

  return result;
}

jbool check_jarg(const char *arg, char **argv, const j_uint argc) {
  if (null_ptr(arg)) {
    return JFALSE;
  }

  jbool res = JFALSE;

  for (j_ullong i = 1; i <= argc; i++) {
    char *s = CALLOC(char, strlen(argv[i]) + 1);
    void **garbage = MALLOC(void *);
    *garbage = VOID_PTR(s);

    strcpy(s, argv[i]);

    res = (!strcmp(arg, s)) ? JTRUE : JFALSE;
    j_gc(garbage, 1);

    if (res) {
      break;
    }
  }

  return res;
}

void j_lstrip(const char c, char *str) {
  if (null_ptr(str)) {
    die(4, "(j_lstrip): No str to strip!");
  }

  size_t len = strlen(str), i = 0;
  size_t new_len = len;

  if (c == '\0' || !len || null_ptr(strchr(str, c))) {
    return;
  }

  while (i <= len && str[i] == c) {
    new_len--;
    i++;
  }

  char *new_str = CALLOC(char, new_len + 1);
  void **garbage = CALLOC(void *, 2);
  garbage[0] = VOID_PTR(new_str);
  garbage[1] = VOID_PTR(str);

  for (i = 0; i <= new_len; i++) {
    new_str[i] = str[len - new_len + i];
  }

  new_str[i] = '\0';

  str = REALLOC(str, char, new_len + 1);

  if (null_ptr(str)) {
    j_gc(garbage, 1);
    die(2, "(j_lstrip): FAILED TO REALLOCATE str!");
  }

  if (null_ptr(stpcpy(str, new_str))) {
    j_gc(garbage, 2);
    die(3, "(j_lstrip): FAILED TO COPY new_str INTO str!");
  }

  j_gc(garbage, 1);
}

void j_rstrip(const char c, char *str) {
  if (null_ptr(str)) {
    die(4, "(j_rstrip): No str to strip!");
  }

  reverse_str(str);
  j_lstrip(c, str);
  reverse_str(str);
}

void j_strip(const char c, char *str) {
  if (null_ptr(str)) {
    die(4, "(j_strip): No str to strip!");
  }

  j_lstrip(c, str);
  j_rstrip(c, str);
}

/// vim:ts=2:sts=2:sw=2:et:ai:si:sta:
