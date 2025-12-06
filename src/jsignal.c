#include <signal.h>
#include <stddef.h>
#include <jeff/jeff.h>
#include <jeff/jsignal.h>

void sig_bootstrap(int *const sigs, const size_t n, void (*fun)(const int)) {
  if (null_ptr(sigs) || !n) {
    return;
  }

  for (size_t i = 0; i < n; i++) {
    signal(sigs[i], fun);
  }

  free(sigs);
}

void sig_handler(const int sig) {
  switch (sig) {
    case SIGINT:
      j_verr("\nCtrl-C detected: %d\n", sig);
      break;

    case SIGTERM:
      j_verr("\nSIGTERM DETECTED: %d\n", sig);
      break;

    case SIGABRT:
      j_verr("\nSIGABRT DETECTED: %d\n", sig);
      break;

    case SIGALRM:
      j_verr("\nSIGALRM DETECTED: %d\n", sig);
      break;

    case SIGHUP:
      j_verr("\nSIGHUP DETECTED: %d\n", sig);
      break;

    default:
      j_verr("\nCaught signal: %d\n", sig);
      break;
  }

  die(sig, NULL);
}

/// vim:ts=2:sts=2:sw=2:et:ai:si:sta:
