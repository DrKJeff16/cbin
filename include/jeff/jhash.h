#if !defined(JHASH_H)
#define JHASH_H 1

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include <jeff/jtypes.h>

// Linked List node
typedef struct node {
  // key is string
  char *key;
  // value is also string
  void *value;
  struct node *next;
} jhash_t;

typedef struct hash_map {
  // Current number of elements in hashMap
  int len;
  // Capacity of hashMap
  int capacity;

  // Hold base address array of linked list
  struct node **arr;
} jhash_map;

void init_jhash(jhash_t *node, char *key, char *value);
void init_jhash_map(jhash_map *mp);

j_llong jhash(jhash_map *mp, char *key);
void jhash_insert(jhash_map *mp, char *key, char *value);
void jhash_delete(jhash_map *mp, char *key);
char *jhash_search(jhash_map *mp, char *key);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* !JHASH_H */

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
