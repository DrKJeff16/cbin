#include <errno.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <jeff/jeff.h>

void die(const int status, char *const msg) {
  if (!null_ptr(msg)) {  /// If message is available
    fprintf(status ? stderr : stdout, "%s\n", msg);
  }

  exit(status);
}

void vdie(const int status, char *const fmt, ...) {
  if (!null_ptr(fmt)) {
    va_list argp;

    va_start(argp, fmt);
    vfprintf(status ? stderr : stdout, fmt, argp);
    va_end(argp);
  }

  exit(status);
}

void exec_vdie(const int status, void (*fun)(void), char *const fmt, ...) {
  if (!null_ptr(fmt)) {
    va_list argp;

    va_start(argp, fmt);
    vfprintf(status ? stderr : stdout, fmt, argp);
    va_end(argp);
  }

  fun();

  exit(status);
}

void errno_vdie(const int status, const int errno_val, char *const fmt, ...) {
  FILE *out = status ? stderr : stdout;

  errno = 0;
  char *err_str = strerror(errno_val);
  if (!null_ptr(err_str)) {
    fprintf(out, "%s\n", err_str);
  }

  if (!null_ptr(fmt)) {
    va_list argp;
    va_start(argp, fmt);
    vfprintf(out, fmt, argp);
    va_end(argp);
  }

  exit(status);
}

/// vim:ts=2:sts=2:sw=2:et:ai:si:sta:noci:nopi:
