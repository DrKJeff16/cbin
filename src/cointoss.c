#include <argp.h>
#include <asm-generic/errno.h>
#include <cointoss.h>
#include <fcntl.h>
#include <jeff/jdie.h>
#include <jeff/jmemory.h>
#include <jeff/jrandom.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const char *argp_program_version = "cointoss 0.2";
const char *argp_program_bug_address = "<g.maxc.fox@protonmail.com>";
static char doc[] = "Cointoss program.";
static char args_doc[] = "[-u] [-r NUM] [-c COUNT] [<X> <Y>]";
static argp_option_t options[] = {
  {
    .name = "verbose",
    .key = 'v',
    .arg = 0,
    .flags = 0,
    .doc = "Verbose mode",
  },
  {
    .name = "total",
    .key = 't',
    .arg = 0,
    .flags = 0,
    .doc = "Whether to show the total stats",
  },
  {
    .name = "count",
    .key = 'c',
    .arg = "COUNT",
    .flags = 0,
    .doc = "How many iterations should be repeated",
  },
  {
    .name = "repeat",
    .key = 'r',
    .arg = "REPEAT",
    .flags = 0,
    .doc = "The repeating cycles amount",
  },
  {
    .name = "no-urandom",
    .key = 'u',
    .arg = 0,
    .flags = 0,
    .doc = "Use /dev/random instead of /dev/urandom",
  },
  { 0 },
};

/* Parse a single option. */
static error_t parse_opt(int key, char *arg, argp_state_t *state) {
  /* Get the input argument from argp_parse, which we
     know is a pointer to our arguments structure. */
  arg_data *arguments = state->input;

  switch (key) {
    case 'u':
      arguments->urandom = JFALSE;
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
        arguments->args[arguments->n_args] = arg;
        arguments->n_args++;
      }
      break;

    case ARGP_KEY_END:
      if (arguments->n_args == 1) {
        argp_failure(state, 1, 0, "%s %s\n", "Can't accept a single positional parameter.",
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

coin_t *init_choices(void) {
  coin_t *c = MALLOC(coin_t);

  c->TAILS = 0;
  c->HEADS = 0;

  return c;
}

void show_total(char *choices[2], char **total, size_t n) {
  coin_t c = { .HEADS = 0, .TAILS = 0 };

  for (size_t i = 0; i < n; i++) {
    if (!strcmp(choices[0], total[i])) {
      c.HEADS++;
      continue;
    }
    if (!strcmp(choices[1], total[i])) {
      c.TAILS++;
      continue;
    }
  }

  printf("\n`%s` ==> %llu\n`%s` ==> %llu\n\n", choices[0], c.HEADS, choices[1], c.TAILS);
  free(total);
}

void decide(const jbool x, coin_t *c) {
  if (null_ptr(c)) {
    j_errno_die(127, EFAULT, "Choices struct is NULL!");
  }

  switch (x) {
    case JFALSE:
      c->HEADS++;
      break;
    case JTRUE:
      c->TAILS++;
      break;
  }
}

jbool fd_toss(const int fd) {
  if (fd < 0) {
    j_errno_vdie(JTRUE, EBADFD, "(fd_toss): %s (fd: %d)\n", "File descriptor unavailable!", fd);
  }

  return fd_urand(fd, JFALSE, JTRUE) ? JTRUE : JFALSE;
}

void verdict(const int fd, coin_t *c, char *coin[2], char **total, const size_t n) {
  if (null_ptr(c)) {
    free(total);
    free(c);
    j_errno_vdie(JTRUE, EFAULT, "(verdict): %s\n", "No available choices!");
  }

  total[n] = coin[(c->HEADS > c->TAILS) ? JTRUE : ((c->TAILS > c->HEADS) ? JFALSE : fd_toss(fd))];
  printf("%s\n", total[n]);

  free(c);
}

static arg_data init_args(void) {
  arg_data arguments = {
    .n_args = 0,
    .urandom = JTRUE,
    .total = JFALSE,
    .verbose = JFALSE,
    .count = 1,
    .rep = 1000000,
    .args[0] = "HEADS",
    .args[1] = "TAILS",
  };

  return arguments;
}

int main(int argc, char **argv) {
  arg_data arguments = init_args();

  argp_parse(&argp, argc, argv, 0, 0, &arguments);

  if (arguments.count == 0) {
    die(JTRUE, "-c can't be 0!");
  }

  char *file = arguments.urandom ? "/dev/urandom" : "/dev/random";
  int fd = open(file, O_RDONLY);
  if (fd < 0) {
    j_errno_vdie(127, ENOENT, "(cointoss): `%s` is unavailable (fd: %d)!\n", file, fd);
  }

  char **total = CALLOC(char *, arguments.count);
  size_t n = 0;
  for (; n < arguments.count; n++) {
    coin_t *c = init_choices();
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
