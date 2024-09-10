#if !defined(JMEMORY_H)
#define JMEMORY_H 1

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#if !defined(MALLOC)
#define MALLOC(type) (type *)malloc(sizeof(type))
#endif /* !MALLOC */

#if !defined(N_MALLOC)
#define N_MALLOC(type, n) (type *)malloc(sizeof(type) * (n))
#endif /* !N_MALLOC */

#if !defined(CALLOC)
#define CALLOC(type, n) (type *)calloc(n, sizeof(type))
#endif /* !CALLOC */

#if !defined(REALLOC)
#define REALLOC(ptr, type, n) (type *)realloc((void *)ptr, sizeof(type) * n)
#endif /* !REALLOC */

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* !JMEMORY_H */

/// vim:ts=4:sts=4:sw=4:et:ai:si:sta:noci:nopi:
