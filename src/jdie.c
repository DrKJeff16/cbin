#include <stdio.h>
#include <stdlib.h>
#include <jeff/jeff.h>

void die(const int status, const char *msg) {
  if (msg != NULL && status) { /// If status is not 0 and message is available
    err(msg);
  } else if (msg != NULL) { /// If status is 0 and message is available
    printf("%s\n", msg);
  }

  exit(status);
}
