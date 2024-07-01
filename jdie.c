#include <jeff/jeff.h>

void die(const bool status, const char *msg) {
  if (msg != NULL && status) {
    err(msg);
  } else if (msg != NULL) {
    printf("%s\n", msg);
  }

  exit(status);
}

void die_exec(const bool status, const char *msg, void (*fun)()) {
  fun();
  die(status, msg);
}
