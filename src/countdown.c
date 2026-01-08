#include <argp.h>
#include <jeff/jeff.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const char *argp_program_version = "countdown 0.1";
const char *argp_program_bug_address = "<g.maxc.fox@protonmail.com>";
static char doc[] = "Customizable countdown program.";
static char args_doc[] = "[-v] [-n INT] [-d INT]";

static argp_option_t options[] = {
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

static void verbose_print(const jbool verbose, const char *txt, FILE *restrict stream) {
  if (!verbose) {
    return;
  }
  if (null_ptr(stream)) {
    stream = stdout;
  }

  fprintf(stream, "%s\n", txt);
}

/* Used by main to communicate with parse_opt. */
typedef struct arguments {
  jbool verbose;
  j_uint duration;
  j_uint num;
} args_t;

/* Parse a single option. */
static error_t parse_opt(int key, char *arg, argp_state_t *state) {
  /* Get the input argument from argp_parse, which we
     know is a pointer to our arguments structure. */
  args_t *arguments = state->input;

  switch (key) {
    case 'v':
      arguments->verbose = JTRUE;
      break;

    case 'n':
      arguments->num = (j_uint)atoi(arg);
      break;

    case 'd':
      arguments->duration = (j_uint)atoi(arg);
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
static argp_t argp = { options, parse_opt, args_doc, doc, NULL, NULL, NULL };

int main(int argc, char **argv) {
  args_t arguments;
  arguments.duration = 1;
  arguments.num = 5;
  arguments.verbose = JFALSE;

  argp_parse(&argp, argc, argv, 0, 0, &arguments);

  char *s = CALLOC(char, 512);
  sprintf(s, "Duration: %ds\nStarts at: %d\n", arguments.duration, arguments.num);

  s = REALLOC(s, char, strlen(s) + 1);

  verbose_print(arguments.verbose, s, NULL);
  free(s);

  while (arguments.num > 0) {
    printf("%d\n", arguments.num);
    sleep(arguments.duration);

    arguments.num--;
  }

  return 0;
}

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
