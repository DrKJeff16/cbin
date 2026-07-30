#include <argp.h>
#include <cointoss.h>
#include <errno.h>
#include <fcntl.h>
#include <jeff/jdie.h>
#include <jeff/jmemory.h>
#include <jeff/jrandom.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "jeff/jtypes.h"

const char *argp_program_version = "cointoss 0.2";
const char *argp_program_bug_address = "<g.maxc.fox@protonmail.com>";
static char doc[] = "Cointoss program.";
static char args_doc[] = "[-u] [-r NUM] [-c COUNT] [<X> <Y>]";
static argp_option_t options[] = {
  { "verbose", 'v', 0, 0, "Verbose mode", 0 },
  { "total", 't', 0, 0, "Whether to show the total stats", 1 },
  { "urandom", 'u', 0, 0, "Use /dev/urandom instead of /dev/random", 1 },
  { "count", 'c', "COUNT", 0, "How many iterations should be repeated", 2 },
  { "repeat", 'r', "REPEAT", 0, "The repeating cycles amount", 2 },
  { 0 },
};

jbool in_arr(char *arr[2], char *const word) {
  jbool result = JFALSE;
  if (!NULL_PTR(word)) {
    for (size_t i = 0; i < 2; i++) {
      if (NULL_PTR(arr[i])) {
        break;
      }
      if (strcmp(arr[i], word) == 0) {
        result = JTRUE;
      }
    }
  }
  return result;
}

static error_t parse_opt(int key, char *arg, argp_state_t *state) {
  /* Get the input argument from argp_parse, which we
     know is a pointer to our arguments structure. */
  arg_data *arguments = state->input;

  switch (key) {
    case 'u':
      arguments->urandom = JTRUE;
      break;

    case 'c':
      arguments->count = (size_t)atoi(arg);
      break;

    case 't':
      arguments->total = JTRUE;
      break;

    case 'r':
      arguments->rep = (j_ullong)atoi(arg);
      break;

    case 'v':
      arguments->verbose = JTRUE;
      break;

    case ARGP_KEY_ARG:
      if (arguments->n_args < 2) {
        jbool is_in_arr = in_arr(arguments->args, arg);
        if (!is_in_arr) {
          arguments->args[arguments->n_args] = arg;
          arguments->n_args++;
        }
      }
      break;

    case ARGP_KEY_END:
      if (arguments->n_args == 0) {
        arguments->args[0] = "HEADS";
        arguments->args[1] = "TAILS";
      } else if (arguments->n_args == 1) {
        argp_failure(state, 1, 0, "%s\n%s\n", "Can't accept a single positional parameter.",
                     "See --help for more information.");
        die(1, NULL);
      }
      break;

    default:
      return ARGP_ERR_UNKNOWN;
  }
  return 0;
}

static argp_t argp = { options, parse_opt, args_doc, doc, NULL, NULL, NULL };

coin_t *init_coin(void) {
  coin_t *coin = MALLOC(coin_t);

  coin->TAILS = 0;
  coin->HEADS = 0;

  return coin;
}

void show_total(char *choices[2], char **total, size_t n) {
  coin_t coin = { .HEADS = 0, .TAILS = 0 };

  for (size_t i = 0; i < n; i++) {
    if (!strcmp(choices[0], total[i])) {
      coin.HEADS++;
      continue;
    }
    if (!strcmp(choices[1], total[i])) {
      coin.TAILS++;
      continue;
    }
  }

  printf("\n`%s` ==> %llu\n`%s` ==> %llu\n\n", choices[0], coin.HEADS, choices[1], coin.TAILS);
  free(total);
}

void decide(const jbool result, coin_t *coin) {
  if (NULL_PTR(coin)) {
    j_errno_die(127, EFAULT, "Choices struct is NULL!");
  }

  switch (result) {
    case JFALSE:
      coin->HEADS++;
      break;
    case JTRUE:
      coin->TAILS++;
      break;
  }
}

jbool fd_toss(const int fd) {
  if (fd < 0) {
    j_errno_vdie(JTRUE, EBADFD, "(fd_toss): %s (fd: %d)\n", "File descriptor unavailable!", fd);
  }

  return fd_urand(fd, JFALSE, JTRUE) ? JTRUE : JFALSE;
}

void verdict(const int fd, coin_t *coin, char *choices[2], char **total, const size_t n) {
  if (NULL_PTR(coin)) {
    free(total);
    free(coin);
    close(fd);
    j_errno_vdie(JTRUE, EFAULT, "(verdict): %s\n", "No available choices!");
  }

  total[n] = choices[(coin->HEADS > coin->TAILS) ? JTRUE : ((coin->TAILS > coin->HEADS) ? JFALSE : fd_toss(fd))];
  printf("%s\n", total[n]);

  free(coin);
}

static arg_data init_args(void) {
  arg_data arguments = {
    .n_args = 0,
    .urandom = JTRUE,
    .total = JFALSE,
    .verbose = JFALSE,
    .count = 1,
    .rep = 1000000,
    .args[0] = NULL,
    .args[1] = NULL,
  };

  return arguments;
}

int main(int argc, char **argv) {
  arg_data arguments = init_args();

  argp_parse(&argp, argc, argv, 0, 0, &arguments);

  if (arguments.count == 0) {
    die(JTRUE, "-c can't be 0!");
  }

  int fd;
  if ((fd = open(arguments.urandom ? "/dev/urandom" : "/dev/random", O_RDONLY)) < 0) {
    j_errno_vdie(127, ENOENT, "(cointoss): `%s` is unavailable (fd: %d)!\n",
                 arguments.urandom ? "/dev/urandom" : "/dev/random", fd);
  }

  char **total = CALLOC(char *, arguments.count);
  size_t n = 0;
  for (; n < arguments.count; n++) {
    coin_t *c = init_coin();
    for (j_ullong j = 0; j < arguments.rep && fd >= 0; j++) {
      if (arguments.verbose) {
        printf("\r%llu%c", j + 1, (j == arguments.rep - 1) ? '\n' : 0);
        fflush(stdout);
      }
      decide(fd_toss(fd), c);
    }

    verdict(fd, c, arguments.args, total, n);
  }
  if (close(fd) != 0) {
    free(total);
    die(JTRUE, "File descriptor could not be closed correctly!");
  }

  if (arguments.total) {
    show_total(arguments.args, total, n);
  }

  die(JFALSE, NULL);
}

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
