#include <jeff/jeff.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yn.h>

static void usage(int code) {
  vdie(code, "%s\n%s\n%s\n", "yn [-N] [-h] <X>\n", "        -h                 print usage",
       "        -N                 use negative result by default\n");
}

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

  int *sigs = CALLOC(int, 6);
  sigs[0] = SIGINT;
  sigs[1] = SIGTERM;
  sigs[2] = SIGABRT;
  sigs[3] = SIGALRM;
  sigs[4] = SIGHUP;
  sigs[5] = SIGKILL;

  sig_bootstrap(sigs, 6, sig_handler);

  if (check_jarg("-h", argv, argc)) {
    usage(0);
  }

  jbool negative = check_jarg("-N", argv, argc);

  char *c = get_no_args(argv, argc);
  char *msg = CALLOC(char, strlen(c) + 1);
  stpcpy(msg, c);

  prompt(msg, negative);
  jbool prev = JFALSE;
  char *in = MALLOC(char);

  void **garbage = CALLOC(void *, 3);
  garbage[0] = VOID_PTR(msg);
  garbage[1] = VOID_PTR(in);
  garbage[2] = VOID_PTR(c);

  *in = getchar();
  do {
    switch (*in) {
      case 'N':
      case 'n':
        j_gc(garbage, 2);
        return 1;

      case 'Y':
      case 'y':
        j_gc(garbage, 2);
        return 0;

      case '\n':
      case '\r':
        if (!prev) {
          j_gc(garbage, 2);
          return negative;
        }
        prev = JFALSE;
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
