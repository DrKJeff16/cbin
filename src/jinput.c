#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <jeff/jeff.h>
#include <jeff/jmemory.h>
#include <jeff/jstring.h>
#include <jeff/jinput.h>

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

  for (J_UINT i = 0; i < len; i++) {
    res[i] = '\0';
  }

  if (!null_ptr(msg)) {
    snprintf(res, len, "%s: ", msg);
  } else {
    snprintf(res, len, "Press any key...: ");
  }

  if (null_ptr(strchr(res, 0))) {
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
    vdie(1, "(buffer_get): %s\n", "Buffer got null'd for some reason");
  }

  return res;
}
