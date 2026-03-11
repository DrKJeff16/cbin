#include <errno.h>
#include <jeff/jdie.h>
#include <jeff/jmemory.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "jeff/jtypes.h"

/**
 * @brief Kill program ekecution with optional output message
 */
void die(const int status, char *const msg) {
  if (!NULL_PTR(msg)) {
    fprintf((!status) ? stdout : stderr, "%s\n", msg);
  }

  exit(status);
}

void vdie(const int status, char *const fmt, ...) {
  if (!NULL_PTR(fmt)) {
    va_list argp;
    va_start(argp, fmt);
    vfprintf((!status) ? stdout : stderr, fmt, argp);
    va_end(argp);
  }

  die(status, NULL);
}

void cond_die(const int status, const jbool cond, char *const msg) {
  if (cond) {
    die(status, msg);
  }
}

void cond_vdie(const int status, const jbool cond, char *const fmt, ...) {
  if (!cond) {
    return;
  }

  if (!NULL_PTR(fmt)) {
    va_list argp;
    va_start(argp, fmt);
    vfprintf((!status) ? stdout : stderr, fmt, argp);
    va_end(argp);
  }

  die(status, NULL);
}

void exec_vdie(const int status, void (*fun)(void), char *const fmt, ...) {
  if (!NULL_PTR(fmt)) {
    va_list argp;
    va_start(argp, fmt);
    vfprintf((!status) ? stdout : stderr, fmt, argp);
    va_end(argp);
  }

  fun();
  die(status, NULL);
}

void j_errno_die(const int status, const int code, char *const msg) {
  FILE *out = (!status) ? stdout : stderr;
  fprintf(out, "%s\n", strerror((code >= EPERM && code <= EHWPOISON) ? code : ENOMSG));

  if (!NULL_PTR(msg)) {  /// If message is available
    fprintf(out, "%s\n", msg);
  }

  die(status, NULL);
}

void j_errno_vdie(const int status, const int code, char *const fmt, ...) {
  FILE *out = (!status) ? stdout : stderr;
  fprintf(out, "%s\n", strerror((code >= EPERM && code <= EHWPOISON) ? code : ENOMSG));

  if (!NULL_PTR(fmt)) {
    va_list argp;
    va_start(argp, fmt);
    vfprintf(out, fmt, argp);
    va_end(argp);
  }

  die(status, NULL);
}

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
