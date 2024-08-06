#include <stdbool.h>
#include <jeff/jeff.h>

bool jxor(const bool x, const bool y) {
  return ((x && !y) || (!x && y));
}
