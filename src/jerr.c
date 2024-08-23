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

  if (msg != NULL) {
    if (fmt != NULL) {
      format = REALLOC(format, char, strlen(fmt) + 1);
      format = strcpy(format, fmt);
    }

    fprintf(stderr, format, msg);
  }
}

void verr(char *const fmt, ...) {
  va_list argp;

  if (fmt != NULL) {
    va_start(argp, fmt);
    vfprintf(stderr, fmt, argp);
    va_end(argp);
  }
}

void exec_verr(void (*fun)(void), char *const fmt, ...) {
  va_list argp;

  if (fmt != NULL) {
    va_start(argp, fmt);
    vfprintf(stderr, fmt, argp);
    va_end(argp);
  }

  fun();
}

/// vim:ts=2:sts=2:sw=2:et:ai:si:sta:noci:nopi:
