#include <lua.h>    // for lua_State
#include <stdio.h>  // for NULL, size_t
#include <stdlib.h>
#include <jeff/jeff.h>     // for err
#include <jeff/jlua.h>     // for jlua_op_buf, _jlua_op, __jlua_o...
#include <jeff/jmemory.h>  // for MALLOC

jlua_op_buf *first_op_buf(jlua_op_buf *const ptr, lua_State *L) {
  if (non_ptr(ptr)) {
    return NULL;
  }

  jlua_op_buf *p = ptr, *placeholder = NULL;
  jlua_op_buf *const safeguard = ptr;

  /* Reset position to beginning of linked list */
  while (p->_prev && NULL != p->_prev) {
    placeholder = p->_prev;
    p = placeholder;

    if (safeguard == p) {
      lua_err(L, "(first_op_buf): %s\n", "Looping list. Aborting");
    }
  }

  if (p && NULL != p) {
    J_ULLONG idx = 1;
    p->index = idx - 1;

    jlua_op_buf *first = p;

    while (p->_next && NULL != p->_next) {
      placeholder = p->_next;
      p = placeholder;

      if (!p || first == p) {
        lua_err(L, "(first_op_buf): %s\n", "Looping list. Aborting");
      }

      p->index = idx;
      idx++;
    }

    p = first;
  }

  return p;
}

jlua_op_buf *last_op_buf(jlua_op_buf *const ptr, lua_State *L) {
  if (!ptr || NULL == ptr) {
    return NULL;
  }

  jlua_op_buf *p = ptr, *placeholder = NULL;
  jlua_op_buf *const safeguard = ptr;

  /* Reset position to beginning of linked list */
  while (p->_next && NULL != p->_next) {
    placeholder = p->_next;
    p = placeholder;

    if (safeguard == p) {
      lua_err(L, "(last_op_buf): %s\n", "Looping list. Aborting");
    }
  }

  return p;
}

void kill_op_buf(jlua_op_buf *const ptr, lua_State *L) {
  if (!ptr || NULL == ptr) {
    return;
  }

  jlua_op_buf *buf = last_op_buf(ptr, L), *placeholder = NULL;

  while (buf->_prev && NULL != buf->_prev) {
    placeholder = buf->_prev;
    buf = placeholder;

    if (buf->_next && NULL != buf->_next) {
      free(buf->_next);
    }

    if (buf->data && NULL != buf->data) {
      free(buf->data);
    }
  }

  free(buf);
}

void new_op_buf(jlua_op_buf *const prev_buf, lua_State *L, const J_ULLONG *const index) {
  if (!prev_buf || NULL == prev_buf) {
    err("(new_op_buf): %s\n", "Predecessor is NULL");
    return;
  }

  prev_buf->_next = MALLOC(jlua_op_buf);
  prev_buf->_next->_next = NULL;
  prev_buf->_next->_prev = prev_buf;
  prev_buf->_next->_type = JLUA_NIL;
  prev_buf->_next->_operator = NOOP;
  prev_buf->_next->index = (index != NULL) ? *index : 0;
  prev_buf->_next->data = NULL;
}

jlua_op_buf *init_op_buf(lua_State *L) {
  jlua_op_buf *buffer = MALLOC(jlua_op_buf);

  buffer->_next = NULL;
  buffer->_prev = NULL;
  buffer->_type = JLUA_NIL;
  buffer->_operator = NOOP;
  buffer->index = 0;
  buffer->data = NULL;

  return buffer;
}

jlua_op_buf *append_op_buf(jlua_op_buf *const ptr, lua_State *L) {
  if (!ptr || NULL == ptr) {
    return NULL;
  }
  if (!L || NULL == L) {
    vdie(127, "(append_op_buf): %s\n", "Lua State has not been initialized");
  }

  jlua_op_buf *p = ptr, *placeholder = NULL;

  /* Reset position to beginning of linked list */
  while (p->_prev && NULL != p->_prev) {
    placeholder = p->_prev;
    p = placeholder;
  }

  J_ULLONG i = 0; /* Start from index 0 */

  /* Go element by element until reaching end */
  while (p->_next && NULL != p->_next) {
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
  new_op_buf(p->_next, L, &i);
  return p->_next;
}

jlua_op_buf *pop_op_buf(jlua_op_buf *const ptr, lua_State *L) {
  if (!ptr || NULL == ptr) {
    return NULL;
  }
  if (!L || NULL == L) {
    vdie(127, "(pop_op_buf): %s\n", "Lua State has not been initialized");
  }

  jlua_op_buf *last = last_op_buf(ptr, L);
  jlua_op_buf *new_last = last->_prev;

  last->_prev = NULL;
  new_last->_next = NULL;

  return last;
}

/// vim:ts=2:sts=2:sw=2:et:ai:si:sta:noci:nopi:
