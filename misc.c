#include <stdio.h>
#include <stdlib.h>
#include <jeff/jeff.h>

char **filter_argv(const int argc, char **argv) {
  if (argc <= 1) {
    return NULL;
  }

  char **result = ALLOC(char*, argc - 1);

  for (unsigned int i = 1; i < (unsigned int)argc; i++) {
    result[i - 1] = argv[i];
  }

  return result;
}

int main(int argc, char **argv) {

  char **args = filter_argv(argc, argv);

  if (args == NULL) {
    die(1, "No arguments given.");
  }

  for (unsigned int i = 0; i < (unsigned int)argc - 1; i++) {
    printf("%s\n", args[i]);
  }

  return 0;
}
