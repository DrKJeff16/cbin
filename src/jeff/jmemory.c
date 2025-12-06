#include <stdlib.h>
#include <jeff/jeff.h>
#include <jeff/jmemory.h>

void j_gc(void **garbage, const size_t n) {
  if (null_ptr(garbage) || !n) {
    return;
  }

  for (size_t i = 0; i < n; i++) {
    free(garbage[i]);
  }

  free(garbage);
}
