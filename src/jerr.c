#include <jeff/jeff.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void err(const char *fmt, const char *msg) {
  if (msg != NULL) {
    if (fmt == NULL) {
      fprintf(stderr, "%s\n", msg);
    } else {
      fprintf(stderr, fmt, msg);
    }
  }
}

void verr(const char *fmt, ...) {
  va_list argp;

  va_start(argp, fmt);
  vfprintf(stderr, fmt, argp);
  va_end(argp);
}

void exec_verr(void (*fun)(void), const char *fmt, ...) {
  va_list argp;

  va_start(argp, fmt);
  vfprintf(stderr, fmt, argp);
  va_end(argp);

  fun();
}
