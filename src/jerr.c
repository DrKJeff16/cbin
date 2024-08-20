#include <stdarg.h>     // for va_end, va_start
#include <stdio.h>      // for fprintf, stderr, vfprintf, NULL, va_list
#include <jeff/jeff.h>  // for err, exec_verr, verr

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

/// vim:ts=2:sts=2:sw=2:et:ai:si:sta:noci:noet:
