#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <jeff/jeff.h>

void die(const int status, char *const msg) {
  FILE *f = status ? stderr : stdout;

  if (!null_ptr(msg)) {  /// If message is available
    fprintf(f, "%s\n", msg);
  }

  exit(status);
}

void vdie(const int status, char *const fmt, ...) {
  FILE *f = status ? stderr : stdout;
  va_list argp;

  if (!null_ptr(fmt)) {
    va_start(argp, fmt);
    vfprintf(f, fmt, argp);
    va_end(argp);
  }

  exit(status);
}

void exec_vdie(const int status, void (*fun)(void), char *const fmt, ...) {
  FILE *f = status ? stderr : stdout;
  va_list argp;

  if (!null_ptr(fmt)) {
    va_start(argp, fmt);
    vfprintf(f, fmt, argp);
    va_end(argp);
  }

  fun();

  exit(status);
}

/// vim:ts=2:sts=2:sw=2:et:ai:si:sta:noci:nopi:
