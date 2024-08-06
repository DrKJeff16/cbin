#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <jeff/jeff.h>

char **filter_argv(const int argc, char **argv) {
  if (argc <= 1) {
    return NULL;
  }

  char **result = CALLOC(char*, argc - 1);

  for (uint i = 1; i < (uint)argc; i++) {
    result[i - 1] = argv[i];
  }

  return result;
}

int main(int argc, char **argv) {
  char **args = filter_argv(argc, argv);

  if (args == NULL) {
    die(1, "No arguments given");
  }

  for (uint i = 0; i < (uint)argc - 1; i++) {
    printf("%s\n", args[i]);
  }

  return 0;
}
