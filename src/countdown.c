#include <argp.h>
#include <jeff/jeff.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

const char *argp_program_version = "countdown 0.1";
const char *argp_program_bug_address = "<g.maxc.fox@protonmail.com>";
static char doc[] = "Customizable countdown program.";
static char args_doc[] = "[-v] [-n INT] [-d INT]";

static struct argp_option options[] = {
  {
    .name = "verbose",
    .key = 'v',
    .arg = 0,
    .flags = 0,
    .doc = "Produce verbose output",
  },
  {
    .name = 0,
    .key = 'n',
    .arg = "NUM",
    .flags = 0,
    .doc = "The starting number",
  },
  {
    .name = "duration",
    .key = 'd',
    .arg = "DURATION",
    .flags = 0,
    .doc = "The duration per countdown",
  },
  { 0 },
};

/* Used by main to communicate with parse_opt. */
struct arguments {
  int verbose;
  int duration;
  int num;
};

/* Parse a single option. */
static error_t parse_opt(int key, char *arg, struct argp_state *state) {
  /* Get the input argument from argp_parse, which we
     know is a pointer to our arguments structure. */
  struct arguments *arguments = state->input;

  switch (key) {
    case 'v':
      arguments->verbose = 1;
      break;

    case 'n':
      arguments->num = atoi(arg);
      break;

    case 'd':
      arguments->duration = atoi(arg);
      break;

    case ARGP_KEY_ARG:
      break;

    case ARGP_KEY_END:
      break;

    default:
      return ARGP_ERR_UNKNOWN;
  }
  return 0;
}

/* Our argp parser. */
static struct argp argp = { options, parse_opt, args_doc, doc, NULL, NULL, NULL };

int main(int argc, char **argv) {
  int *sigs = CALLOC(int, 6);
  sigs[0] = SIGINT;
  sigs[1] = SIGTERM;
  sigs[2] = SIGABRT;
  sigs[3] = SIGALRM;
  sigs[4] = SIGHUP;
  sigs[5] = SIGKILL;

  sig_bootstrap(sigs, 6, sig_handler);

  struct arguments arguments;
  arguments.duration = 1;
  arguments.num = 5;
  arguments.verbose = 0;

  argp_parse(&argp, argc, argv, 0, 0, &arguments);

  while (arguments.num > 0) {
    printf("%d\n", arguments.num);
    sleep(arguments.duration);

    arguments.num--;
  }

  return 0;
}
