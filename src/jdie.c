#include <jeff/jeff.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void die(const int status, const char *msg) {
  if (msg != NULL && status) { /// If status is not 0 and message is available
    err(NULL, msg);
  } else if (msg != NULL) { /// If status is 0 and message is available
    printf("%s\n", msg);
  }

  exit(status);
}

void vdie(const int status, const char *fmt, ...) {
  va_list argp;

  if (fmt != NULL) {
    va_start(argp, fmt);

    FILE *f = stdout;

    if (status) {
      f = stderr;
    }

    vfprintf(f, fmt, argp);
  }

  va_end(argp);

  die(status, NULL);
}

void exec_vdie(const int status, void (*fun)(void), const char *fmt, ...) {
  va_list argp;

  if (fmt != NULL) {
    va_start(argp, fmt);

    FILE *f = stdout;

    if (status) {
      f = stderr;
    }

    vfprintf(f, fmt, argp);
  }

  va_end(argp);

  fun();

  die(status, NULL);
}
