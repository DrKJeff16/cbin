#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <jeff/jeff.h>
#include <yn.h>

char *get_no_args(char **const argv, const int argc) {
  char *c = CALLOC(char, 9);
  const char *fallback = "Confirm";
  stpcpy(c, fallback);

  for (size_t i = 1; i <= (size_t)argc; i++) {
    if (*argv[i] != '-') {
      c = REALLOC(c, char, strlen(argv[i]) + 1);
      stpcpy(c, argv[i]);
      return c;
    }
  }

  return c;
}

jbool set_default(char *const arg) {
  if (null_ptr(arg)) {
    return JFALSE;
  }

  j_uint res;
  switch (*arg) {
    case 'n':
    case 'N':
    case '1':
      res = JTRUE;
      break;

    case 'y':
    case 'Y':
    case '0':
    default:
      res = JFALSE;
      break;
  }

  return res;
}

void prompt(char *msg, const jbool fallback) {
  j_rstrip(' ', msg);
  j_rstrip('?', msg);
  j_rstrip(' ', msg);
  j_rstrip('.', msg);
  j_rstrip(' ', msg);
  printf("%s? [%s]: ", msg, (fallback == JFALSE) ? "Y/n" : "y/N");
}

int main(int argc, char **argv) {
  argc--;
  signal(SIGINT, sig_handler);
  signal(SIGTERM, sig_handler);
  signal(SIGABRT, sig_handler);

  jbool fallback = check_jarg("-N", argv, argc);
  char *c = get_no_args(argv, argc);
  char *msg = CALLOC(char, strlen(c) + 1);
  stpcpy(msg, c);

  prompt(msg, fallback);
  jbool prev = JFALSE;
  char *in = MALLOC(char);
  *in = getchar();
  do {
    switch (*in) {
      case 78:   /// 'N'
      case 110:  /// 'n'
        free(msg);
        free(in);
        return 1;

      case 89:   /// 'Y'
      case 121:  /// 'y'
        free(msg);
        free(in);
        return 0;

      case 10:  /// '\n'
      case 13:  /// '\r'
        if (!prev) {
          free(msg);
          free(in);
          return fallback;
        }
        prompt(msg, fallback);
        break;

      default:
        prev = JTRUE;
        break;
    }
  } while ((*in = getchar()));

  free(in);
  free(msg);
  return 127;
}
