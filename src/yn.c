#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <jeff/jeff.h>
#include <yn.h>

char *get_no_args(jbool no_args, char *positive) {
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
  signal(SIGINT, sig_handler);
  signal(SIGTERM, sig_handler);
  signal(SIGABRT, sig_handler);
  argc--;

  char *c = get_no_args(((argc == 0) ? JTRUE : JFALSE), argv[1]);
  char *msg = CALLOC(char, strlen(c) + 1);
  stpcpy(msg, c);

  char in;
  jbool prev = JFALSE;
  prompt(msg);
  while ((in = getchar())) {
    if (in == '\r') {
      prompt(msg);
      continue;
    }

    switch (in) {
      case 'n':
      case 'N':
        free(msg);
        return 1;

      case 'y':
      case 'Y':
        free(msg);
        return 0;

      case 10:  /// Newline
        {
          if (!prev) {
            free(msg);
            return 0;
          }
          prompt(msg);
          break;
        }
      default:
        prev = JTRUE;
        break;
    }
  }

  free(msg);
  return 127;
}
