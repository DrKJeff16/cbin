#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <jeff/jeff.h>
#include <yn.h>

char *get_no_args(const jbool no_args, char *const positive) {
  return (no_args || null_ptr(positive)) ? "Confirm" : positive;
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
  printf("%s? [%s]: ", (fallback == JFALSE) ? "Y/n" : "y/N", msg);
}

int main(int argc, char **argv) {
  argc--;
  signal(SIGINT, sig_handler);
  signal(SIGTERM, sig_handler);
  signal(SIGABRT, sig_handler);

  char *c = get_no_args(((argc == 0) ? JTRUE : JFALSE), argv[1]);
  jbool fallback = set_default((argc >= 2) ? argv[2] : NULL);
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
