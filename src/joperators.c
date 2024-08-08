#include <jeff/jeff.h>

jbool jxor(const jbool x, const jbool y) {
  return ((x && !y) || (!x && y));
}
