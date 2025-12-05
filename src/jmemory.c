#include <stdlib.h>
#include <jeff/jeff.h>
#include <jeff/jmemory.h>

void j_gc(void **garbage, const size_t n) {
  for (size_t i = 0; i < n; i++) {
    free(garbage[i]);
  }

  free(garbage);
}
