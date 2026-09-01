#include <jeff/jhash.h>
#include <jeff/jmemory.h>
#include <jeff/jtypes.h>
#include <stdlib.h>
#include <string.h>

void init_jhash(jhash_t *node, char *key, char *value) {
  node->key = key;
  node->value = value;
  node->next = NULL;
}

void init_jhash_map(jhash_map *mp) {
  mp->capacity = 100; /*!< Default capacity in this case */
  mp->len = 0;
  mp->arr = CALLOC(jhash_t *, mp->capacity);
}

j_llong jhash(jhash_map *mp, char *key) {
  j_llong sum = 0, factor = 31;
  for (size_t i = 0; i < strlen(key); i++) {
    sum = ((sum % mp->capacity) + (((j_llong)key[i]) * factor) % mp->capacity) % mp->capacity;
    factor = ((factor % __INT64_MAX__) * (31 % __INT64_MAX__)) % __INT64_MAX__;
  }

  return sum;
}

void jhash_insert(jhash_map *mp, char *key, char *value) {
  j_llong bucket_index = jhash(mp, key);
  jhash_t *new_node = MALLOC(jhash_t);

  init_jhash(new_node, key, value);

  if (!NULL_PTR(mp->arr[bucket_index])) {
    new_node->next = mp->arr[bucket_index];
  }

  mp->arr[bucket_index] = new_node;
}

void jhash_delete(jhash_map *mp, char *key) {
  j_llong bucket_index = jhash(mp, key);
  jhash_t *prev_node = NULL;
  jhash_t *curr_node = mp->arr[bucket_index];
  while (!NULL_PTR(curr_node)) {
    if (strcmp(key, curr_node->key) == 0) {
      if (curr_node == mp->arr[bucket_index]) {
        mp->arr[bucket_index] = curr_node->next;
      } else {
        prev_node->next = curr_node->next;
      }
      free(curr_node);
      break;
    }
    prev_node = curr_node;
    curr_node = curr_node->next;
  }
}

char *jhash_search(jhash_map *mp, char *key) {
  j_llong bucket_index = jhash(mp, key);
  jhash_t *bucket_head = mp->arr[bucket_index];
  while (!NULL_PTR(bucket_head)) {
    if (bucket_head->key == key) {  // Key is found in the hashMap
      return bucket_head->value;
    }
    bucket_head = bucket_head->next;
  }

  char *error_msg = CALLOC(char, 25);
  error_msg = "Oops! No data found.\n";
  return error_msg;
}

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
