#include <jeff/jeff.h>
#include <jeff/jlua.h>
#include <jeff/jmemory.h>
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

jlua_sbuf *init_jlua_sbuf(lua_State *L, const size_t stack_len) {
  jlua_sbuf *buffer = MALLOC(jlua_sbuf);
  buffer->L = L;
  buffer->stack_len = stack_len;

  return buffer;
}

void new_op_buf(jlua_op_buf *predecessor, const unsigned long long *i) {
  if (predecessor == NULL) {
    err("(new_op_buf): %s\n", "Predecessor is NULL");
    return;
  }

  predecessor->_next = MALLOC(jlua_op_buf);;
  predecessor->_next->_next = NULL;
  predecessor->_next->_prev = predecessor;
  predecessor->_next->_type = JLUA_NIL;
  predecessor->_next->_operator = NOOP;
  predecessor->_next->index = *i;
  predecessor->_next->data = NULL;
}

jlua_op_buf *init_op_buf(void) {
  jlua_op_buf *buffer = MALLOC(jlua_op_buf);

  buffer->_next = NULL;
  buffer->_prev = buffer;
  buffer->_type = JLUA_NIL;
  buffer->_operator = NOOP;
  buffer->index = 0;
  buffer->data = NULL;

  return buffer;
}

jlua_op_buf *append_op_buf(jlua_op_buf *ptr) {
  if (ptr == NULL) {
    return NULL;
  }

  jlua_op_buf *p = ptr;
  jlua_op_buf *placeholder;

  /* Reset position to beginning of linked list */
  while (NULL != p->_prev) {
    placeholder = p->_prev;
    p = placeholder;
  }

  unsigned long long i = 0; /* Start from index 0 */

  /* Go element by element until reaching end */
  while (NULL != p->_next) {
    /* Correct index of each element if not aligned */
    if (i != p->index) {
      p->index = i;
    }

    /* And now to the next one */
    placeholder = p->_next;
    p = placeholder;
    i++;
  }

  /* Once end is reached initialize new element and return its memory address */
  new_op_buf(p->_next, &i);
  return p->_next;
}
