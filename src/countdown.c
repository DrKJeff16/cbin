#include <argp.h>
#include <jeff/jeff.h>
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
typedef struct arguments {
  jbool verbose;
  int duration;
  int num;
} args_t;

/* Parse a single option. */
static error_t parse_opt(int key, char *arg, struct argp_state *state) {
  /* Get the input argument from argp_parse, which we
     know is a pointer to our arguments structure. */
  args_t *arguments = state->input;

  switch (key) {
    case 'v':
      arguments->verbose = JTRUE;
      break;

    case 'n':
      arguments->num = atoi(arg);
      break;

    case 'd':
      arguments->duration = atoi(arg);
      break;

    case ARGP_KEY_ARG:
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
  args_t arguments;
  arguments.duration = 1;
  arguments.num = 5;
  arguments.verbose = JFALSE;

  argp_parse(&argp, argc, argv, 0, 0, &arguments);

  while (arguments.num > 0) {
    printf("%d\n", arguments.num);
    sleep(arguments.duration);

    arguments.num--;
  }

  return 0;
}

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
