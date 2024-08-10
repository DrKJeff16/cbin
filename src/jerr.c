#include <stdio.h>
#include <stdlib.h>
#include <jeff/jeff.h>

void err(const char *fmt, const char *msg) {
  if (msg != NULL) {
    if (fmt == NULL) {
      fprintf(stderr, "%s\n", msg);
    } else {
      fprintf(stderr, fmt, msg);
    }
  }
}
