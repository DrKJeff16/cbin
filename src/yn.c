#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <yn.h>

char *get_no_args(const jbool no_args, char *const positive) {
  return (no_args || null_ptr(positive)) ? "Confirm" : positive;
}

void prompt(char *msg) {
  j_rstrip(' ', msg);
  j_rstrip('?', msg);
  j_rstrip(' ', msg);
  j_rstrip('.', msg);
  j_rstrip(' ', msg);
  printf("%s? [Y/n]: ", msg);
}

int main(int argc, char **argv) {
  argc--;
  signal(SIGINT, sig_handler);
  signal(SIGTERM, sig_handler);
  signal(SIGABRT, sig_handler);

  char *c = get_no_args(((argc == 0) ? JTRUE : JFALSE), argv[1]);
  char *msg = CALLOC(char, strlen(c) + 1);
  stpcpy(msg, c);

  prompt(msg);
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
          return 0;
        }
        prompt(msg);
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
