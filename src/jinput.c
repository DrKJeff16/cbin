#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <jeff/jeff.h>

char *buffer_get(char *const msg, size_t *const buf_len) {
  size_t len = 0;

  if (null_ptr(buf_len)) {
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

  if (!null_ptr(msg)) {
    snprintf(res, len, "%s: ", msg);
  } else {
    snprintf(res, len, "Press any key...: ");
  }

  char *chr = strchr(res, 0);
  if (null_ptr(chr)) {
    res = REALLOC(res, char, len + 1);
    res[len] = '\0';
  } else {
    size_t new_len = strnlen(res, len);

    if (new_len < len) {
      res = REALLOC(res, char, new_len);
      str_append_nul(res);
    }
  }

  if (null_ptr(res)) {
    j_errno_vdie(1, EFAULT, "(buffer_get): %s\n", "Buffer got null'd for some reason");
  }

  return res;
}

/// vim:ts=2:sts=2:sw=2:et:ai:si:sta:noci:nopi:
