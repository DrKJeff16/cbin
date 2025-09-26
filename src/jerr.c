#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jeff/jeff.h>

void j_err(char *const fmt, char *const msg) {
  char *format = CALLOC(char, 4);
  strcpy(format, "%s\n");

  if (!null_ptr(fmt)) {
    format = REALLOC(format, char, strlen(fmt) + 1);

    char *cpy = strcpy(format, fmt);

    if (null_ptr(cpy)) {
      free(format);
      return;
    }
  }

  if (!null_ptr(msg)) {
    fprintf(stderr, format, msg);
  } else {
    fprintf(stderr, "%s\n", format);
  }

  free(format);
}

void j_verr(char *const fmt, ...) {
  if (null_ptr(fmt)) {
    return;
  }

  va_list argp;

  va_start(argp, fmt);
  vfprintf(stderr, fmt, argp);
  va_end(argp);
}

void j_errno_err(const int code, char *const fmt, char *const msg) {
  char *format = CALLOC(char, 4);
  strcpy(format, "%s\n");

  int e_code = (code >= EPERM && code <= EHWPOISON) ? code : ENOMSG;
  j_err(format, strerror(e_code));

  if (!null_ptr(fmt)) {
    format = REALLOC(format, char, strlen(fmt) + 1);

    char *cpy = stpcpy(format, fmt);

    if (null_ptr(cpy)) {
      free(format);
      return;
    }
  }

  if (!null_ptr(msg)) {
    j_err(format, msg);
  }

  free(format);
}

void j_errno_verr(const int code, char *const fmt, ...) {
  int e_code = (code >= EPERM && code <= EHWPOISON) ? code : ENOMSG;
  j_err("%s\n", strerror(e_code));

  if (null_ptr(fmt)) {
    return;
  }

  va_list argp;

  va_start(argp, fmt);
  vfprintf(stderr, fmt, argp);
  va_end(argp);
}

void j_exec_verr(void (*fun)(void), char *const fmt, ...) {
  if (!null_ptr(fmt)) {
    va_list argp;

    va_start(argp, fmt);
    vfprintf(stderr, fmt, argp);
    va_end(argp);
  }

  fun();
}

/// vim:ts=2:sts=2:sw=2:et:ai:si:sta:
