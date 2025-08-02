#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jeff/jeff.h>
#include <jeff/jmemory.h>
#include <jeff/jstring.h>

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

    verr("(str_append_nul): %s\n", "Unable to copy `new_str` back to `str`");
  }

  free(new_str);
  free(str_og);
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

    free(c);
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

    free(c);
  }
}

void capitalize(char *str, jbool *use_dot) {
  if (null_ptr(str)) {
    verr("%s\n", "NULL string cannot be capitalized");
    return;
  }

  jbool space = JTRUE;

  char capital_d = 'a' - 'A';

  for (size_t i = 0; i < strlen(str) + 1; i++) {
    if ((str[i] >= 'a' && str[i] <= 'z') && space) {
      space = JFALSE;
      str[i] -= capital_d;
    } else if ((str[i] >= 'A' && str[i] <= 'Z') && !space) {
      str[i] += capital_d;
    } else if ((str[i] >= 'A' && str[i] <= 'Z') && space) {
      space = JFALSE;
    } else if (str[i] == ' ' || str[i] == '\n') {
      space = JTRUE;
    }
  }
}

// char *parse_esc(char *const old_str) {
//   if (null_ptr(old_str)) {
//     return NULL;
//   }
//   if (!strchr(old_str, '\\')) {
//     return old_str;
//   }
//
//   size_t len = strlen(old_str);
//   char *res = CALLOC(char, len + 1);
//
//   jbool esc = JFALSE;
//
//   size_t i = 0;
//
//   /* FIXME: Fix this */
//   while (i < len) {
//     if (!esc) {
//       esc = (old_str[i] == '\\') ? JTRUE : JFALSE;
//     } else if (old_str[i] == '\\') {
//       esc = JFALSE;
//     } else {
//       switch (old_str[i]) {
//         case 'n':
//           i--;
//           len--;
//           res = REALLOC(res, char, len);
//           res[i] = '\n';
//           break;
//         case 'r':
//           i--;
//           len--;
//           res = REALLOC(res, char, len);
//           res[i] = '\r';
//           break;
//         case 'a':
//           i--;
//           len--;
//           res = REALLOC(res, char, len);
//           res[i] = '\a';
//           break;
//         case 'e':
//           i--;
//           len--;
//           res = REALLOC(res, char, len);
//           res[i] = '\e';
//           break;
//         case 'v':
//           i--;
//           len--;
//           res = REALLOC(res, char, len);
//           res[i] = '\v';
//           break;
//         case 'f':
//           i--;
//           len--;
//           res = REALLOC(res, char, len);
//           res[i] = '\f';
//           break;
//         case '"':
//           i--;
//           len--;
//           res = REALLOC(res, char, len);
//           res[i] = '\"';
//           break;
//         case '?':
//           i--;
//           len--;
//           res = REALLOC(res, char, len);
//           res[i] = '\?';
//           break;
//         default:
//           break;
//       }
//     }
//
//     i++;
//   }
//
//   return res;
// }

jbool compare_strv(char **const argv, const size_t len) {
  if (null_ptr(argv)) {
    err("%s\n", "`argv`is NULL");
    return JFALSE;
  }

  if (len < 2) {
    verr("`argv` must be of length 2 or greater (%d)\n", len);
    return JFALSE;
  }

  for (size_t i = 1; i < len; i++) {
    if (!strcmp(argv[0], argv[i])) {
      return JFALSE;
    }
  }

  return JTRUE;
}

void reverse_str(char *str) {
  if (null_ptr(str)) {
    return;
  }

  char *rev = str_reversed(str);

  if (null_ptr(rev)) {
    return;
  }

  stpcpy(str, rev);
}

char *str_reversed(char *const str) {
  if (null_ptr(str)) {
    return NULL;
  }

  const size_t len = strlen(str);
  char *result = CALLOC(char, len + 1);

  for (size_t i = 1; i <= len; i++) {
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
    strcpy(s, argv[i]);

    res = (!strcmp(arg, s)) ? JTRUE : JFALSE;

    free(s);

    if (res) {
      break;
    }
  }

  return res;
}

/// vim:ts=2:sts=2:sw=2:et:ai:si:sta:noci:nopi:
