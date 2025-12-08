#if !defined(JSWAP_H)
#define JSWAP_H 1

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#define J_SWAP(x, y)   \
  do {                 \
    typeof(x) __x = x; \
    typeof(y) __y = y; \
    x = __y;           \
    y = __x;           \
  } while (0)

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* !JSWAP_H */

/// vim:ts=2:sts=2:sw=2:et:ai:si:sta:
