#ifndef JMEMORY_H
#define JMEMORY_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdlib.h>

#ifndef MALLOC
#define MALLOC(type) (type *)malloc(sizeof(type))
#endif /* !MALLOC */

#ifndef N_MALLOC
#define N_MALLOC(type, n) (type *)malloc(sizeof(type) * (n))
#endif /* !N_MALLOC */

#ifndef CALLOC
#define CALLOC(type, n) (type *)calloc(n, sizeof(type))
#endif /* !CALLOC */

#ifndef REALLOC
#define REALLOC(ptr, type, n) (type *)realloc((void *)ptr, sizeof(type) * n)
#endif /* !REALLOC */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !JMEMORY_H */

/// vim:ts=4:sts=4:sw=4:et:ai:si:sta:noci:nopi:
