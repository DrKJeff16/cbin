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
    die(0, "No arguments provided!");
  }

  size_t i = 0;
  char **valid = CALLOC(char *, argc);

  for (; i < (size_t)argc; i++) {
    size_t len = strlen(argv[i + 1]);
    valid[i] = CALLOC(char, len + 1);

    if (null_ptr(stpcpy(valid[i], argv[i + 1]))) {
      free_valid(valid, argc);
      return 1;
    }

    printf("%zu: `%s`", i, valid[i]);
    strip('-', valid[i]);
    printf("  ===>  `%s`\n", valid[i]);
  }

  free_valid(valid, argc);
  return 0;
}
