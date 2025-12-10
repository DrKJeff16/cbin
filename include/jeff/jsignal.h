#if !defined(JSIGNAL_H)
#define JSIGNAL_H 1

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include <stddef.h>

void sig_handler(const int sig);
void sig_bootstrap(int *sigs, const size_t n, void (*fun)(const int));

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* !JSIGNAL_H */

/// vim:ts=2:sts=2:sw=2:et:ai:si:sta:
