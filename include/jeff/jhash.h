#if !defined(JHASH_H)
#define JHASH_H 1

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include "jtypes.h"

/** \addtogroup libjeff
 * @{
 */

/**
 * \struct node
 */
struct node {
  char *key;         /*!< A string value that acts as the key */
  char *value;       /*!< The string value */
  struct node *next; /*!< The next node pointer, or `NULL` if it doesn't exist */
};

/**
 * \typedef jhash_t
 * \brief Linked List node
 */
typedef struct node jhash_t;

/**
 * \struct hash_map
 */
struct hash_map {
  int len;       /*!< Current number of elements in hashMap */
  int capacity;  /*!< Capacity of hashMap */
  jhash_t **arr; /*!< Hold base address array of linked list */
};

/**
 * \typedef jhash_map
 * \brief Hash table struct typedef
 */
typedef struct hash_map jhash_map;

/**
 * \brief Initialize a linked list element of a hash table
 * \param node The pointer to initialize the element on
 * \param key The key of the element
 * \param value The value of the element
 */
void init_jhash(jhash_t *node, char *key, char *value);

/**
 * \brief Initialize a hash table
 * \param mp The pointer to initialize the hash table on
 */
void init_jhash_map(jhash_map *mp);

/**
 * \brief Custom hash function
 *
 * This retrieves the hashed value of the key in a hash table
 *
 * \param mp The hash table to be analyze
 * \param key The key to be hashed
 */
j_llong jhash(jhash_map *mp, char *key);

/**
 * \brief Insert a value to an element from the hash table
 * \param mp The hash table to be operated on
 * \param key The key value to match
 * \param value The value type to insert
 */
void jhash_insert(jhash_map *mp, char *key, char *value);

/**
 * \brief Delete an element from the hash table, given a key
 * \param mp The hash table to be operated on
 * \param key The key value to match
 */
void jhash_delete(jhash_map *mp, char *key);

/**
 * \brief Search an element from the hash table, given a key
 * \param mp The hash table to be searched on
 * \param key The key value to match
 * \return The value that matches the key, or `NULL` if not found
 */
char *jhash_search(jhash_map *mp, char *key);

/** @} */

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* !JHASH_H */

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
