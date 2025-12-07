#include <asm-generic/errno.h>
#include <jeff/jeff.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

void j_err(char *const fmt, char *const msg) {
  char *format = CALLOC(char, 4);
  void **garbage = MALLOC(void *);
  *garbage = VOID_PTR(format);

  stpcpy(format, "%s\n");

  if (!null_ptr(fmt)) {
    format = REALLOC(format, char, strlen(fmt) + 1);
    stpcpy(format, fmt);
  }
  if (!null_ptr(msg)) {
    fprintf(stderr, format, msg);
  } else {
    fprintf(stderr, "%s\n", format);
  }

  j_gc(garbage, 1);
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
  void **garbage = MALLOC(void *);
  *garbage = VOID_PTR(format);

  int e_code = (code >= EPERM && code <= EHWPOISON) ? code : ENOMSG;

  stpcpy(format, "%s\n");
  j_err(format, strerror(e_code));

  if (!null_ptr(fmt)) {
    format = REALLOC(format, char, strlen(fmt) + 1);
  }
  if (!null_ptr(msg)) {
    j_err(format, msg);
  }

  j_gc(garbage, 1);
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
