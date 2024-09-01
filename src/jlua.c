#include <errno.h>
#include <string.h>
#include <lua.h>
#include <stdio.h>
#include <stdlib.h>
#include <jeff/jeff.h>
#include <jeff/jmemory.h>
#include <jeff/jlua.h>

char *jlua_op_char(const jlua_operator x) {
  switch (x) {
    case PUSH:
      return "PUSH";
    case CHECK_STACK:
      return "StackCheck";
    case NOOP:
    default:
      return "NOOP";
  }
}

char *jlua_type_char(const jlua_type x) {
  switch (x) {
    case JLUA_BOOL:
      return "boolean";
    case JLUA_LSTR:
      return "lstring";
    case JLUA_NUM:
      return "number";
    case JLUA_STR:
      return "string";
    case JLUA_NIL:
    default:
      return "nil";
  }
}

jlua_op_buf *first_op_buf(jlua_op_buf *const ptr, lua_State *L) {
  if (null_ptr(ptr)) {
    verr("(first_op_buf): %s\n%s\n", strerror(EFAULT), "Argument is NULL");
    return NULL;
  }

  jlua_op_buf *const safeguard = ptr;
  jlua_op_buf *p = ptr, *placeholder = NULL;

  /* Reset position to beginning of linked list */
  while (!null_ptr(p->_prev)) {
    placeholder = p->_prev;
    p = placeholder;

    if (safeguard == p) {
      lua_err(L, "(first_op_buf): %s\n%s\n", strerror(E2BIG), "Looping list");
    }
  }

  if (null_ptr(p)) {
    lua_err(L, "(first_op_buf): %s\n%s\n", strerror(EFAULT), "NULL pointer");
  }

  return p;
}

jlua_op_buf *last_op_buf(jlua_op_buf *const ptr, lua_State *L) {
  if (null_ptr(ptr)) {
    verr("(last_op_buf): %s\n%s\n", strerror(EFAULT), "Argument is NULL");
    return NULL;
  }

  jlua_op_buf *const safeguard = ptr;
  jlua_op_buf *p = ptr, *placeholder = NULL;

  /* Reset position to beginning of linked list */
  while (!null_ptr(p->_next)) {
    placeholder = p->_next;
    p = placeholder;

    if (safeguard == p) {
      lua_err(L, "(last_op_buf): %s\n%s\n", strerror(E2BIG), "Looping list");
    }
  }

  if (null_ptr(p)) {
    lua_err(L, "(last_op_buf): %s\n%s\n", strerror(EFAULT), "NULL pointer");
  }

  return p;
}

void kill_op_buf(jlua_op_buf *const ptr, lua_State *L) {
  if (null_ptr(ptr)) {
    verr("(kill_op_buf): %s\n%s\n", strerror(EFAULT), "Nothing to kill, returning");
    return;
  }

  jlua_op_buf *buf = last_op_buf(ptr, L), *placeholder = NULL;

  while (!null_ptr(buf->_prev)) {
    placeholder = buf->_prev;
    buf = placeholder;

    printf("Freeing address: %p\n", JCAST(void *, buf->_next));
    free(buf->_next);
  }

  printf("Freeing final address: %p\n", JCAST(void *, buf));
  free(buf);
}

void new_op_buf(jlua_op_buf *const prev_buf, lua_State *L, J_ULLONG *const index) {
  if (null_ptr(prev_buf)) {
    verr("(new_op_buf): %s\n%s\n", strerror(EFAULT), "Predecessor is NULL");
    return;
  }

  prev_buf->_next = MALLOC(jlua_op_buf);
  prev_buf->_next->_next = NULL;
  prev_buf->_next->_prev = prev_buf;
  prev_buf->_next->_type = JLUA_NIL;
  prev_buf->_next->_operator = NOOP;
  prev_buf->_next->index = (!null_ptr(index)) ? *index : 0;
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
  if (null_ptr(ptr)) {
    return NULL;
  }
  if (null_ptr(L)) {
    vdie(127, "(append_op_buf): %s\n%s\n", strerror(ESRCH), "Lua State has not been initialized");
  }

  jlua_op_buf *p = first_op_buf(ptr, L), *placeholder = NULL;

  J_ULLONG i = 0; /* Start from index 0 */

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
    verr("NULL Lua state, can't print\n");
    return;
  }
  if (null_ptr(ptr)) {
    verr("NULL buffer, can't print\n");
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
