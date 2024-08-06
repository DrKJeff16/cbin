#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <jeff/jeff.h>

void err(const char *msg) {
  if (msg != NULL) {
#ifdef ERR
    ERR(msg);
#else
    fprintf(stderr, "%s\n", msg);
#endif // !ERR
  }
}
