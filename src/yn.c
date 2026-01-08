#include <argp.h>
#include <jeff/jeff.h>
#include <stdio.h>
#include <string.h>
#include <yn.h>

const char *argp_program_version = "yn 1.0";
const char *argp_program_bug_address = "<g.maxc.fox@protonmail.com>";
static char doc[] = "An easy \"Yes/No\" prompt.";
static char args_doc[] = "[-N] [<X>]";

static argp_option_t options[] = {
  {
    .name = "invert",
    .key = 'N',
    .arg = 0,
    .flags = 0,
    .doc = "Invert the default result from pressing `\\n` only",
  },
  { 0 },
};

/* Used by main to communicate with parse_opt. */
typedef struct arguments {
  jbool invert;
  char *args[1];
} args_t;

/* Parse a single option. */
static error_t parse_opt(int key, char *arg, argp_state_t *state) {
  /* Get the input argument from argp_parse, which we
     know is a pointer to our arguments structure. */
  args_t *arguments = state->input;

  switch (key) {
    case 'N':
      arguments->invert = JTRUE;
      break;

    case ARGP_KEY_ARG:
      arguments->args[0] = arg;
      break;

    case ARGP_KEY_END:
      break;

    default:
      return ARGP_ERR_UNKNOWN;
  }
  return 0;
}

static argp_t argp = { options, parse_opt, args_doc, doc, NULL, NULL, NULL };

void prompt(char *msg, const jbool negative) {
  printf("%s [%s]: ", msg, (!negative) ? "Y/n" : "y/N");
}

int main(int argc, char **argv) {
  args_t arguments;
  arguments.invert = JFALSE;
  arguments.args[0] = "Confirm?";

  argp_parse(&argp, argc, argv, 0, 0, &arguments);

  prompt(arguments.args[0], arguments.invert);
  jbool prev = JFALSE;
  char in;
  in = getchar();
  do {
    switch (in) {
      case 'N':
      case 'n':
        return 1;

      case 'Y':
      case 'y':
        return 0;

      case '\n':
      case '\r':
        if (!prev) {
          return arguments.invert;
        }
        prompt(arguments.args[0], arguments.invert);
        prev = JFALSE;
        break;

      default:
        prev = JTRUE;
        break;
    }
  } while ((in = getchar()));

  return 127;
}

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
