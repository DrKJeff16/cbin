#include <errno.h>
#include <jeff/jdie.h>
#include <jeff/jinput.h>
#include <jeff/jmemory.h>
#include <jeff/jstring.h>
#include <stdio.h>
#include <string.h>

#include "jeff/jtypes.h"

char *buffer_get(char *const msg, size_t *const buf_len) {
  size_t len = 0;

  if (NULL_PTR(buf_len)) {
    len = 1024;
  } else {
    len = *buf_len;
  }

  if (!len) {
    return NULL;
  }

  len++;

  char *res = CALLOC(char, len);

  for (j_ulong i = 0; i < len; i++) {
    res[i] = '\0';
  }

  if (!NULL_PTR(msg)) {
    snprintf(res, len, "%s: ", msg);
  } else {
    snprintf(res, len, "Press any key...: ");
  }

  char *chr = strchr(res, 0);
  if (NULL_PTR(chr)) {
    res = REALLOC(res, char, len + 1);
    res[len] = '\0';
  } else {
    size_t new_len = strnlen(res, len);

    if (new_len < len) {
      res = REALLOC(res, char, new_len);
      str_append_nul(res);
    }
  }

  if (NULL_PTR(res)) {
    j_errno_vdie(1, EFAULT, "(buffer_get): %s\n", "Buffer got null'd for some reason");
  }

  return res;
}

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
