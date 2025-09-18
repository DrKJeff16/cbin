#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <jeff/jeff.h>
#include <yn.h>

char *get_no_args(jbool no_args, char *positive) {
  return no_args ? "Confirm" : positive;
}

int main(int argc, char **argv) {
  signal(SIGINT, sig_handler);
  signal(SIGTERM, sig_handler);
  signal(SIGABRT, sig_handler);

  argc--;

  jbool no_args = (argc == 0) ? JTRUE : JFALSE;

  while (JTRUE) {
    char input[4];
    char *msg = CALLOC(char, strlen(get_no_args(no_args, argv[1])) + 1);
    stpcpy(msg, get_no_args(no_args, argv[1]));

    j_rstrip(' ', msg);
    j_rstrip('?', msg);
    j_rstrip(' ', msg);
    j_rstrip('.', msg);
    j_rstrip(' ', msg);

    printf("%s? [Y/N]: ", msg);
    free(msg);

    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;

    switch (input[0]) {
      case 'y':
      case 'Y':
        return 0;

      case 'n':
      case 'N':
        return 1;

      default:
        break;
    }
  }

  return 127;
}
