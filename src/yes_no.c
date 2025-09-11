#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <jeff/jeff.h>
#include <yes_no.h>

void free_valid(char **valid, const size_t argc) {
  for (size_t i = 0; i < argc; i++) {
    free(valid[i]);
  }

  free(valid);
}

void sig_handler(int sig) {
  vdie(sig, "\nCaught signal %d\n", sig);
}

int main(int argc, char **argv) {
  signal(SIGINT, sig_handler);
  signal(SIGTERM, sig_handler);

  argc--;

  if (argc == 0) {
    j_err("%s\n", "No arguments provided!");
    return 127;
  }

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

  while (JTRUE) {
    char input[4];
    char *msg = CALLOC(char, strlen(argv[1]) + 1);
    stpcpy(msg, argv[1]);
    j_rstrip('?', msg);

    printf("%s?[Y/N]: ", msg);
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
