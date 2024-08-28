#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jeff/jeff.h>
#include <jeff/jmemory.h>

void err(char *const fmt, char *const msg) {
  char *format = CALLOC(char, 4);
  format[0] = '%';
  format[1] = 's';
  format[2] = '\n';
  format[3] = '\0';

  if (!null_ptr(fmt)) {
    format = REALLOC(format, char, strlen(fmt) + 1);
    if (null_ptr(stpcpy(format, fmt))) {
      free(format);
      return;
    }
  }

  if (!null_ptr(msg)) {
    fprintf(stderr, format, msg);
  }

  free(format);
}

void verr(char *const fmt, ...) {
  if (null_ptr(fmt)) {
    return;
  }

  va_list argp;

  va_start(argp, fmt);
  vfprintf(stderr, fmt, argp);
  va_end(argp);
}

void exec_verr(void (*fun)(void), char *const fmt, ...) {
  if (null_ptr(fmt)) {
    return;
  }

  va_list argp;

  va_start(argp, fmt);
  vfprintf(stderr, fmt, argp);
  va_end(argp);

  fun();
}

/// vim:ts=2:sts=2:sw=2:et:ai:si:sta:noci:nopi:
