#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <jeff/jeff.h>
#include <yn.h>

char *get_no_args(char **const argv, const int argc) {
  char *c = CALLOC(char, 9);
  const char *fallback = "Confirm?";
  stpcpy(c, fallback);

  for (size_t i = 1; i <= (size_t)argc; i++) {
    if (*argv[i] != '-') {
      c = REALLOC(c, char, strlen(argv[i]) + 1);
      stpcpy(c, argv[i]);
      break;
    }
  }

  return c;
}

void prompt(char *msg, const jbool negative) {
  j_rstrip(' ', msg);
  printf("%s [%s]: ", msg, (!negative) ? "Y/n" : "y/N");
}

int main(int argc, char **argv) {
  argc--;
  signal(SIGINT, sig_handler);
  signal(SIGTERM, sig_handler);
  signal(SIGABRT, sig_handler);

  jbool negative = check_jarg("-N", argv, argc);
  char *c = get_no_args(argv, argc);
  char *msg = CALLOC(char, strlen(c) + 1);
  stpcpy(msg, c);

  prompt(msg, negative);
  jbool prev = JFALSE;
  char *in = MALLOC(char);

  void **garbage = CALLOC(void *, 2);
  garbage[0] = (void *)msg;
  garbage[1] = (void *)in;

  *in = getchar();
  do {
    switch (*in) {
      case 78:   /// 'N'
      case 110:  /// 'n'
        j_gc(garbage, 2);
        return 1;

      case 89:   /// 'Y'
      case 121:  /// 'y'
        j_gc(garbage, 2);
        return 0;

      case 10:  /// '\n'
      case 13:  /// '\r'
        if (!prev) {
          j_gc(garbage, 2);
          return negative;
        }
        prompt(msg, negative);
        break;

      default:
        prev = JTRUE;
        break;
    }
  } while ((*in = getchar()));

  j_gc(garbage, 2);
  return 127;
}
