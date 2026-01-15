#include <argp.h>
#include <stdio.h>
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

/* Parse a single option. */
static error_t parse_opt(int key, char *arg, argp_state_t *state) {
  /* Get the input argument from argp_parse, which we
     know is a pointer to our arguments structure. */
  arg_data *arguments = state->input;

  switch (key) {
    case 'N':
      arguments->invert = JTRUE;
      break;

    case ARGP_KEY_ARG:
      if (!arguments->n_args) {
        arguments->args[0] = arg;
        arguments->n_args++;
      }
      break;

    case ARGP_KEY_END:
      break;

    default:
      return ARGP_ERR_UNKNOWN;
  }
  return 0;
}

static argp_t argp = { options, parse_opt, args_doc, doc, NULL, NULL, NULL };

static void prompt(const char *restrict msg, const jbool negative) {
  printf("%s [%s]: ", msg, (!negative) ? "Y/n" : "y/N");
}

static arg_data init_args(void) {
  arg_data arguments;
  arguments.invert = JFALSE;
  arguments.n_args = 0;
  arguments.args[0] = "Confirm?";

  return arguments;
}

int main(int argc, char **argv) {
  arg_data arguments = init_args();

  argp_parse(&argp, argc, argv, 0, 0, &arguments);

  prompt(arguments.args[0], arguments.invert);
  jbool prev = JFALSE;
  char in;
  while ((in = getchar())) {
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
  }

  return 127;
}

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
