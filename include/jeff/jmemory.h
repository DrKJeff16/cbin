#ifndef JMEMORY_H
#define JMEMORY_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdlib.h>

#ifndef MALLOC
#define MALLOC(type) (type*)malloc(sizeof(type))
#endif /* !MALLOC */

#ifndef CALLOC
#define CALLOC(type, n) (type*)calloc(n, sizeof(type))
#endif /* !CALLOC */

#ifndef REALLOC
#define REALLOC(ptr, type, n) (type*)realloc(ptr, sizeof(type) * n)
#endif /* !REALLOC */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !JMEMORY_H */
