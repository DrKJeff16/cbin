#include <errno.h>
#include <string.h>
#include <lua.h>
#include <stdio.h>
#include <stdlib.h>
#include <jeff/jeff.h>

char *jlua_op_char(const jlua_operator x) {
  switch (x) {
    case PUSH:
      return "PUSH";
    case CHECK_STACK:
      return "CHECK_STACK";
    case NOOP:
    default:
      return "NOOP";
  }
}

char *jlua_type_char(const jlua_type x) {
  switch (x) {
    case JLUA_LSTR:
      return "lstring";
    case JLUA_STR:
      return "string";
    case JLUA_NUM:
      return "number";
    case JLUA_BOOL:
      return "boolean";
    case JLUA_NIL:
    default:
      return "nil";
  }
}

jlua_op_buf *first_op_buf(jlua_op_buf *const ptr, lua_State *L) {
  if (null_ptr(L)) {
    j_errno_vdie(127, ESRCH, "(first_op_buf): %s\n", "Lua State has not been initialized");
  }
  if (null_ptr(ptr)) {
    j_errno_verr(EFAULT, "(first_op_buf): %s\n", "Argument is NULL");
    return NULL;
  }

  jlua_op_buf *const safeguard = ptr;
  jlua_op_buf *p = ptr, *placeholder = NULL;

  /* Reset position to beginning of linked list */
  while (!null_ptr(p->_prev)) {
    placeholder = p->_prev;
    p = placeholder;

    if (safeguard == p) {
      j_errno_verr(E2BIG, "(first_op_buf): %s\n", "Looping list");
      return NULL;
    }
  }

  if (null_ptr(p)) {
    lua_err(L, "(first_op_buf): %s\n%s\n", strerror(EFAULT), "NULL pointer");
  }

  return p;
}

jlua_op_buf *last_op_buf(jlua_op_buf *const ptr, lua_State *L) {
  if (null_ptr(L)) {
    j_errno_vdie(127, ESRCH, "(last_op_buf): %s\n", "Lua State has not been initialized");
  }
  if (null_ptr(ptr)) {
    j_errno_verr(EFAULT, "(last_op_buf): %s\n", "Argument is NULL");
    return NULL;
  }

  jlua_op_buf *const safeguard = ptr;
  jlua_op_buf *p = ptr, *placeholder = NULL;

  /* Reset position to beginning of linked list */
  while (!null_ptr(p->_next)) {
    placeholder = p->_next;
    p = placeholder;

    if (safeguard == p) {
      j_errno_verr(E2BIG, "(last_op_buf): %s\n", "Looping list");
      return NULL;
    }
  }

  if (null_ptr(p)) {
    lua_err(L, "(last_op_buf): %s\n%s\n", strerror(EFAULT), "NULL pointer");
  }

  return p;
}

void kill_op_buf(jlua_op_buf *const ptr, lua_State *L) {
  if (null_ptr(L)) {
    j_errno_vdie(127, ESRCH, "(kill_op_buf): %s\n", "Lua State has not been initialized");
  }
  if (null_ptr(ptr)) {
    j_errno_verr(EFAULT, "(kill_op_buf): %s\n", "Nothing to kill, returning");
    return;
  }

  jlua_op_buf *buf = last_op_buf(ptr, L), *placeholder = NULL;

  if (null_ptr(buf)) {
    j_errno_verr(EFAULT, "(kill_op_buf): %s\n", "Couldn't retrieve buffer end");
    return;
  }

  while (!null_ptr(buf->_prev)) {
    placeholder = buf->_prev;
    buf = placeholder;

    printf("Freeing address: %p\n", JCAST(void *, buf->_next));
    free(buf->_next);
  }

  printf("Freeing final address: %p\n", JCAST(void *, buf));
  free(buf);
}

void new_op_buf(jlua_op_buf *const prev_buf, lua_State *L, j_ullong *const index) {
  if (null_ptr(L)) {
    j_errno_vdie(127, ESRCH, "(new_op_buf): %s\n", "Lua State has not been initialized");
  }
  if (null_ptr(prev_buf)) {
    j_errno_verr(EFAULT, "(new_op_buf): %s\n", "Predecessor is NULL");
    return;
  }

  jlua_op_buf *buf = last_op_buf(prev_buf, L);

  buf->_next = MALLOC(jlua_op_buf);
  buf->_next->_next = NULL;
  buf->_next->_prev = prev_buf;
  buf->_next->_type = JLUA_NIL;
  buf->_next->_operator = NOOP;
  buf->_next->index = (!null_ptr(index)) ? *index : 0;
  buf->_next->data = NULL;
}

jlua_op_buf *init_op_buf(lua_State *L) {
  if (null_ptr(L)) {
    j_errno_vdie(127, ESRCH, "(init_op_buf): %s\n", "Lua State has not been initialized");
  }
  jlua_op_buf *buffer = MALLOC(jlua_op_buf);

  buffer->_next = NULL;
  buffer->_prev = NULL;
  buffer->_type = JLUA_NIL;
  buffer->_operator = NOOP;
  buffer->index = 0;
  buffer->data = NULL;

  return buffer;
}

void fix_buf_indeces(jlua_op_buf *const ptr, lua_State *L) {
  if (null_ptr(L)) {
    j_errno_vdie(127, ESRCH, "(fix_buf_indeces): %s\n", "Lua State has not been initialized");
  }
  if (null_ptr(ptr)) {
    lua_err(L, "(fix_buf_indeces): %s\n%s\n", strerror(EFAULT), "Null pointer");
  }

  jlua_op_buf *buf = first_op_buf(ptr, L), *placeholder = NULL;

  if (null_ptr(buf)) {
    j_errno_verr(EFAULT, "(fix_buf_indeces): %s\n", "Couldn't retrieve buffer start");
    return;
  }

  jlua_op_buf *const safeguard = buf;

  j_ullong i = 0;

  do {
    if (i != buf->index) {
      buf->index = i;
    }
    i++;

    placeholder = buf->_next;
    buf = placeholder;
  } while (!null_ptr(buf) && buf != safeguard);
}

jlua_op_buf *append_op_buf(jlua_op_buf *const ptr, lua_State *L) {
  if (null_ptr(L)) {
    j_errno_vdie(127, ESRCH, "(append_op_buf): %s\n", "Lua State has not been initialized");
  }
  if (null_ptr(ptr)) {
    return NULL;
  }

  jlua_op_buf *p = first_op_buf(ptr, L), *placeholder = NULL;

  j_ullong i = 0; /* Start from index 0 */

  /* Go element by element until reaching end */
  while (!null_ptr(p->_next)) {
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

void op_buf_iprint(jlua_op_buf *const ptr, lua_State *L) {
  if (null_ptr(L)) {
    j_verr("NULL Lua state, can't print\n");
    return;
  }
  if (null_ptr(ptr)) {
    j_verr("NULL buffer, can't print\n");
    return;
  }

  printf("Slot %llu ==> %p\n", ptr->index, JCAST(void *, ptr));

  if (!null_ptr(ptr->_prev)) {
    printf("|    Previous Slot (%llu) ==> %p\n", ptr->_prev->index, JCAST(void *, ptr->_prev));
  } else {
    printf("|    Previous Slot ==> NULL\n");
  }
  if (!null_ptr(ptr->_next)) {
    printf("|    Next Slot (%llu) ==> %p\n", ptr->_next->index, JCAST(void *, ptr->_next));
  } else {
    printf("|    Next Slot ==> NULL\n");
  }

  char *_char = jlua_type_char(ptr->_type);
  printf("|    Type ==> %s\n", !null_ptr(_char) ? _char : "unknown");

  _char = jlua_op_char(ptr->_operator);
  printf("|    Operator ==> %s\n", !null_ptr(_char) ? _char : "NOOP");

  if (!null_ptr(ptr->data)) {
    printf("|    Data ==> %p\n", JCAST(void *, ptr->data));
  } else {
    printf("|    Data ==> NULL\n");
  }
}

/// vim:ts=2:sts=2:sw=2:et:ai:si:sta:noci:nopi:
