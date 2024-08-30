#include <stdlib.h>
#include <jeff/jeff.h>

jbool jxor(const J_LLONG x, const J_LLONG y) {
  return ((x && !y) || (!x && y));
}

jbool null_ptr(void *const ptr) {
  return !ptr || ptr == NULL;
}

/// vim:ts=2:sts=2:sw=2:et:ai:si:sta:noci:nopi:
