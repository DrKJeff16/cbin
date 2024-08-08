#include <stdio.h>
#include <stdlib.h>
#include <jeff/jeff.h>

void err(const char *msg) {
  if (msg != NULL) {
    fprintf(stderr, "%s\n", msg);
  }
}
