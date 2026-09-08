#include <argp.h>
#include <cointoss.h>
#include <errno.h>
#include <fcntl.h>
#include <jeff/jdie.h>
#include <jeff/jmemory.h>
#include <jeff/jrandom.h>
#include <jeff/jtypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *argp_program_version = "cointoss 0.2";
const char *argp_program_bug_address = "<g.maxc.fox@protonmail.com>";
static char doc[] = "Coin tossing program";
static char args_doc[] = "[-u] [-r NUM] [-c COUNT] [<X> <Y>]";
static argp_option_t options[] = {
  { "exit-code", 'E', 0, 0, "Whether to exit the program depending on the result of the coin toss (HEADS is 0)", 2 },
  { "count", 'c', "COUNT", 0, "How many iterations should be repeated", 2 },
  { "repeat", 'r', "REPEAT", 0, "The repeating cycles amount", 2 },
  { "total", 't', 0, 0, "Whether to show the total stats", 1 },
  { "urandom", 'u', 0, 0, "Use /dev/urandom instead of /dev/random", 1 },
  { "verbose", 'v', 0, 0, "Verbose mode", 0 },
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
  cointoss_arg_t *args = state->input;
  switch (key) {
    case 'E':
      args->by_exit_code = JTRUE;
      break;

    case 'u':
      args->urandom = JTRUE;
      break;

    case 'c':
      args->count = (size_t)atoi(arg);
      break;

    case 't':
      args->total = JTRUE;
      break;

    case 'r':
      args->rep = (j_ullong)atoi(arg);
      break;

    case 'v':
      args->verbose = JTRUE;
      break;

    case ARGP_KEY_ARG:
      if (args->n_args < 2 && !in_arr(args->args, arg)) {
        args->args[args->n_args] = arg;
        args->n_args++;
      }
      break;

    case ARGP_KEY_END:
      if (args->n_args == 0) {
        args->args[HEADS] = "HEADS";
        args->args[TAILS] = "TAILS";
      } else if (args->n_args != 2) {
        vdie(127, "%s\n%s\n", "Can only accept two positional arguments!", "See --help for more information.");
      }
      break;

    default:
      return ARGP_ERR_UNKNOWN;
  }
  return 0;
}

static argp_t argp = { options, parse_opt, args_doc, doc, NULL, NULL, NULL };

j_ullong *init_coin(void) {
  j_ullong *coin = CALLOC(j_ullong, 2);

  coin[HEADS] = 0;
  coin[TAILS] = 0;

  return coin;
}

void show_total(cointoss_arg_t *arguments, cointoss_value_t *ec, char **const total, const size_t n) {
  char **choices = arguments->args;
  j_ullong coin[2] = { [HEADS] = 0, [TAILS] = 0 };
  for (size_t i = 0; i < n; i++) {
    if (!strcmp(choices[HEADS], total[i])) {
      coin[HEADS]++;
    } else if (!strcmp(choices[TAILS], total[i])) {
      coin[TAILS]++;
    }
  }

  *ec = (coin[HEADS] > coin[TAILS]) ? HEADS : TAILS;

  if (arguments->total) {
    printf("\n(HEADS): `%s` ==> %llu\n(TAILS): `%s` ==> %llu\n\n", choices[HEADS], coin[HEADS], choices[TAILS],
           coin[TAILS]);
  }
}

void decide(const cointoss_value_t result, j_ullong *coin) {
  if (!NULL_PTR(coin)) {
    coin[result]++;
  }
}

cointoss_value_t fd_toss(cointoss_arg_t *arguments) {
  return fd_urand(open(arguments->urandom ? "/dev/urandom" : "/dev/random", O_RDONLY), HEADS, TAILS) ? HEADS : TAILS;
}

void verdict(cointoss_arg_t *args, j_ullong *const coin, char *choices[2], char **total, const size_t n) {
  if (NULL_PTR(coin) && !NULL_PTR(total)) {
    free(total);
    j_errno_die(JTRUE, EFAULT, "(verdict): No available choices!");
  } else if (NULL_PTR(total) && !NULL_PTR(coin)) {
    free(coin);
    j_errno_die(JTRUE, EFAULT, "(verdict): Total is unavailable!");
  } else if (NULL_PTR(total) && NULL_PTR(coin)) {
    j_errno_die(JTRUE, EFAULT, "(verdict): Total and available choices are unavailable!");
  }

  total[n] = choices[cointoss_max_coin(args, coin)];
  printf("%s\n", total[n]);
}

cointoss_value_t cointoss_max_coin(cointoss_arg_t *args, j_ullong *coin) {
  if (coin[TAILS] == coin[HEADS]) {
    coin[fd_toss(args)]++;
  }
  return (coin[HEADS] > coin[TAILS]) ? HEADS : TAILS;
}

static cointoss_arg_t init_args(void) {
  cointoss_arg_t arguments = {
    .args[0] = NULL,
    .args[1] = NULL,
    .by_exit_code = JFALSE,
    .count = 1,
    .n_args = 0,
    .rep = 1000000,
    .total = JFALSE,
    .urandom = JTRUE,
    .verbose = JFALSE,
  };

  return arguments;
}

int main(int argc, char **argv) {
  cointoss_arg_t arguments = init_args();

  argp_parse(&argp, argc, argv, 0, 0, &arguments);

  if (arguments.count == 0) {
    die(JTRUE, "-c can't be 0!");
  }

  char **total = CALLOC(char *, arguments.count);
  size_t n = 0;
  cointoss_value_t ec = HEADS;
  for (; n < arguments.count; n++) {
    j_ullong *c = init_coin();
    for (j_ullong j = 0; j < arguments.rep; j++) {
      if (arguments.verbose) {
        printf("\r%llu%c", j + 1, (j == arguments.rep - 1) ? '\n' : 0);
        fflush(stdout);
      }
      decide(fd_toss(&arguments) ? TAILS : HEADS, c);
    }
    verdict(&arguments, c, arguments.args, total, n);
    free(c);
  }

  show_total(&arguments, &ec, total, n);

  free(total);
  return (arguments.by_exit_code) ? ec : 0;
}

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
