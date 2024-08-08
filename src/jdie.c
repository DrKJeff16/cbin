#include <stdio.h>
#include <stdlib.h>
#include <jeff/jeff.h>

void die(const int status, const char *msg) {
  if (msg != NULL && status) {
    err(msg);
  } else if (msg != NULL) {
    printf("%s\n", msg);
  }

  exit(status);
}

static void die_exec(const int status, const char *msg, void (*fun)(void)) {
  fun();
  die(status, msg);
}
