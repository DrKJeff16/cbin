#include <errno.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <jeff/jeff.h>

void die(const int status, char *const msg) {
  if (!null_ptr(msg)) {  /// If message is available
    fprintf(output(status), "%s\n", msg);
  }

  exit(status);
}

void vdie(const int status, char *const fmt, ...) {
  if (!null_ptr(fmt)) {
    va_list argp;

    va_start(argp, fmt);
    vfprintf(output(status), fmt, argp);
    va_end(argp);
  }

  exit(status);
}

void exec_vdie(const int status, void (*fun)(void), char *const fmt, ...) {
  if (!null_ptr(fmt)) {
    va_list argp;

    va_start(argp, fmt);
    vfprintf(output(status), fmt, argp);
    va_end(argp);
  }

  fun();

  exit(status);
}

void errno_die(const int status, const int code, char *const msg) {
  FILE *out = output(status);
  fprintf(out, "%s\n", strerror((code >= EPERM && code <= EHWPOISON) ? code : ENOMSG));

  if (!null_ptr(msg)) {  /// If message is available
    fprintf(out, "%s\n", msg);
  }

  exit(status);
}

void errno_vdie(const int status, const int code, char *const fmt, ...) {
  FILE *out = output(status);

  fprintf(out, "%s\n", strerror((code >= EPERM && code <= EHWPOISON) ? code : ENOMSG));

  if (!null_ptr(fmt)) {
    va_list argp;
    va_start(argp, fmt);
    vfprintf(out, fmt, argp);
    va_end(argp);
  }

  exit(status);
}

/// vim:ts=4:sts=4:sw=4:et:ai:si:sta:noci:nopi:
