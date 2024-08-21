#include <jeff/jeff.h>

jbool jxor(const jbool x, const jbool y) {
  return ((x && !y) || (!x && y));
}

/// vim:ts=4:sts=4:sw=4:et:ai:si:sta:noci:nopi:
