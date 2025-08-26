#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jeff/jeff.h>
#include <yes_no.h>

void free_valid(char **valid, const size_t argc) {
  for (size_t i = 0; i < argc; i++) {
    free(valid[i]);
  }

  free(valid);
}

int main(int argc, char **argv) {
  argc--;

  if (argc == 0) {
    j_err("%s\n", "No arguments provided!");
    return 1;
  }

  size_t i = 0, len = (size_t)argc;
  char **valid = CALLOC(char *, len);

  for (; i < len; i++) {
    size_t len = strlen(argv[i + 1]);
    valid[i] = CALLOC(char, len + 1);

    if (null_ptr(stpcpy(valid[i], argv[i + 1]))) {
      free_valid(valid, len);
      return 1;
    }

    printf("%zu: `%s`", i, valid[i]);
    j_strip('-', valid[i]);
    printf("  ===>  `%s`\n", valid[i]);
  }

  free_valid(valid, len);
  return 0;
}
