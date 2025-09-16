#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <jeff/jeff.h>

void sig_handler(const int sig) {
  switch (sig) {
    case SIGINT:
      {
        fprintf(stderr, "\nCtrl-C detected: %d\n", sig);
        break;
      }

    default:
      {
        fprintf(stderr, "\nCaught signal %d\n", sig);
        break;
      }
  }

  exit(sig);
}

/// vim:ts=2:sts=2:sw=2:et:ai:si:sta:noci:nopi:
