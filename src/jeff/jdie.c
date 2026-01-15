#include <asm-generic/errno.h>
#include <jeff/jdie.h>
#include <jeff/jeff.h>
#include <jeff/jmemory.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Kill program ekecution with optional output message
 */
void die(const int status, char *const msg) {
  if (!null_ptr(msg)) {
    fprintf(J_OUTPUT(status), "%s\n", msg);
  }

  exit(status);
}

void vdie(const int status, char *const fmt, ...) {
  if (!null_ptr(fmt)) {
    va_list argp;
    va_start(argp, fmt);
    vfprintf(J_OUTPUT(status), fmt, argp);
    va_end(argp);
  }

  exit(status);
}

void cond_die(const int status, const jbool cond, char *const msg) {
  if (!cond) {
    return;
  }

  die(status, msg);
}

void cond_vdie(const int status, const jbool cond, char *const fmt, ...) {
  if (!cond) {
    return;
  }

  va_list argp;
  va_start(argp, fmt);
  vdie(status, fmt, argp);
  va_end(argp);
}

void exec_vdie(const int status, void (*fun)(void), char *const fmt, ...) {
  if (!null_ptr(fmt)) {
    va_list argp;
    va_start(argp, fmt);
    vfprintf(J_OUTPUT(status), fmt, argp);
    va_end(argp);
  }

  fun();
  exit(status);
}

void j_errno_die(const int status, const int code, char *const msg) {
  FILE *out = J_OUTPUT(status);
  fprintf(out, "%s\n", strerror((code >= EPERM && code <= EHWPOISON) ? code : ENOMSG));

  if (!null_ptr(msg)) {  /// If message is available
    fprintf(out, "%s\n", msg);
  }

  exit(status);
}

void j_errno_vdie(const int status, const int code, char *const fmt, ...) {
  FILE *out = J_OUTPUT(status);
  fprintf(out, "%s\n", strerror((code >= EPERM && code <= EHWPOISON) ? code : ENOMSG));

  if (!null_ptr(fmt)) {
    va_list argp;
    va_start(argp, fmt);
    vfprintf(out, fmt, argp);
    va_end(argp);
  }

  exit(status);
}

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
