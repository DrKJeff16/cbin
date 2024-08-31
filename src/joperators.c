#include <jeff/jeff.h>

jbool jxor(const J_LLONG x, const J_LLONG y) {
  return ((x && !y) || (!x && y));
}

/// vim:ts=2:sts=2:sw=2:et:ai:si:sta:noci:nopi:
