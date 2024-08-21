#include <stdarg.h>     // for va_end, va_start
#include <stdio.h>      // for fprintf, stderr, vfprintf, NULL, va_list
#include <jeff/jeff.h>  // for err, exec_verr, verr

void err(char *const fmt, char *const msg) {
  if (msg != NULL) {
    if (fmt == NULL) {
      fprintf(stderr, "%s\n", msg);
    } else {
      fprintf(stderr, fmt, msg);
    }
  }
}

void verr(char *const fmt, ...) {
  va_list argp;

  va_start(argp, fmt);
  vfprintf(stderr, fmt, argp);
  va_end(argp);
}

void exec_verr(void (*fun)(void), char *const fmt, ...) {
  va_list argp;

  va_start(argp, fmt);
  vfprintf(stderr, fmt, argp);
  va_end(argp);

  fun();
}

/// vim:ts=4:sts=4:sw=4:et:ai:si:sta:noci:nopi:
