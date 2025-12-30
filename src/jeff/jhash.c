#include <jeff/jeff.h>
#include <jeff/jhash.h>
#include <jeff/jmemory.h>
#include <string.h>

// like constructor
void init_jhash(jhash_t *node, char *key, char *value) {
  node->key = key;
  node->value = value;
  node->next = NULL;
}

// like constructor
void init_jhash_map(jhash_map *mp) {
  // Default capacity in this case
  mp->capacity = 100;
  mp->len = 0;

  // array of size = 1
  mp->arr = CALLOC(jhash_t *, mp->capacity);
  return;
}

j_llong jhash(jhash_map *mp, char *key) {
  j_llong bucketIndex;
  j_llong sum = 0, factor = 31;
  for (size_t i = 0; i < strlen(key); i++) {
    // sum = sum + (ascii value of
    // char * (primeNumber ^ x))...
    // where x = 1, 2, 3....n
    sum = ((sum % mp->capacity) + (((j_llong)key[i]) * factor) % mp->capacity) % mp->capacity;

    // factor = factor * prime
    // number....(prime
    // number) ^ x
    factor = ((factor % __INT16_MAX__) * (31 % __INT16_MAX__)) % __INT16_MAX__;
  }

  bucketIndex = sum;
  return bucketIndex;
}

void insert(jhash_map *mp, char *key, char *value) {
  j_llong bucketIndex = jhash(mp, key);
  jhash_t *newNode = MALLOC(jhash_t);

  init_jhash(newNode, key, value);

  if (!null_ptr(mp->arr[bucketIndex])) {
    newNode->next = mp->arr[bucketIndex];
  }

  mp->arr[bucketIndex] = newNode;
}

void delete(jhash_map *mp, char *key) {
  j_llong bucketIndex = jhash(mp, key);

  jhash_t *prevNode = NULL;
  jhash_t *currNode = mp->arr[bucketIndex];

  while (!null_ptr(currNode)) {
    if (strcmp(key, currNode->key) == 0) {
      if (currNode == mp->arr[bucketIndex]) {
        mp->arr[bucketIndex] = currNode->next;
      } else {
        prevNode->next = currNode->next;
      }
      free(currNode);
      break;
    }
    prevNode = currNode;
    currNode = currNode->next;
  }
}

char *search(jhash_map *mp, char *key) {
  j_llong bucketIndex = jhash(mp, key);

  jhash_t *bucketHead = mp->arr[bucketIndex];
  while (!null_ptr(bucketHead)) {
    // Key is found in the hashMap
    if (bucketHead->key == key) {
      return bucketHead->value;
    }
    bucketHead = bucketHead->next;
  }

  char *errorMssg = CALLOC(char, 25);
  errorMssg = "Oops! No data found.\n";
  return errorMssg;
}
