#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <jeff/jeff.h>
#include <yn.h>

void free_valid(char **valid, const size_t argc) {
  for (size_t i = 0; i < argc; i++) {
    free(valid[i]);
  }

  free(valid);
}

char *get_no_args(jbool no_args, char *positive) {
  return no_args ? "Confirm" : positive;
}

int main(int argc, char **argv) {
  signal(SIGINT, sig_handler);
  signal(SIGTERM, sig_handler);
  signal(SIGABRT, sig_handler);

  argc--;

  // size_t i = 0, len = (size_t)argc;
  // char **valid = CALLOC(char *, len);

  // for (; i < len; i++) {
  //   size_t len = strlen(argv[i + 1]);
  //   valid[i] = CALLOC(char, len + 1);
  //
  //   if (null_ptr(stpcpy(valid[i], argv[i + 1]))) {
  //     free_valid(valid, len);
  //     return 1;
  //   }
  //
  //   printf("%zu: `%s`", i, valid[i]);
  //   j_strip('-', valid[i]);
  //   printf("  ===>  `%s`\n", valid[i]);
  // }

  // free_valid(valid, len);

  jbool *no_args = MALLOC(jbool);
  *no_args = (argc == 0) ? JTRUE : JFALSE;

  while (JTRUE) {
    char input[4];
    char *msg = CALLOC(char, strlen(get_no_args(*no_args, argv[1])) + 1);
    stpcpy(msg, get_no_args(*no_args, argv[1]));

    j_rstrip(' ', msg);
    j_rstrip('?', msg);
    j_rstrip(' ', msg);
    j_rstrip('.', msg);
    j_rstrip(' ', msg);

    printf("%s? [Y/N]: ", msg);
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;

    free(msg);

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

  free(no_args);

  return 127;
}
