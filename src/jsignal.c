#include <signal.h>
#include <jeff/jeff.h>

void sig_handler(const int sig) {
  switch (sig) {
    case SIGINT:
      {
        j_verr("\nCtrl-C detected: %d\n", sig);
        break;
      }

    case SIGTERM:
      {
        j_verr("\nSIGTERM DETECTED: %d\n", sig);
        break;
      }

    default:
      {
        j_verr("\nCaught signal %d\n", sig);
        break;
      }
  }

  die(sig, NULL);
}

/// vim:ts=2:sts=2:sw=2:et:ai:si:sta:noci:nopi:
