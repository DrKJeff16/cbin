#include <argp.h>
#include <jeff/jdie.h>
#include <jeff/jmemory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yn.h>

const char *argp_program_version = "yn 1.0";
const char *argp_program_bug_address = "<g.maxc.fox@protonmail.com>";
static char doc[] = "An easy \"Yes/No\" prompt.";
static char args_doc[] = "[-N] [-c INT] [<X>]";
static argp_option_t options[] = {
  { "exit-code", 'c', "CODE", 0, "The desired failure exit code", 0 },
  { "invert", 'N', 0, 0, "Invert the default result from pressing `\\n` only", 0 },
  { 0 },
};

/* Parse a single option. */
static error_t parse_opt(int key, char *arg, argp_state_t *state) {
  /* Get the input argument from argp_parse, which we
     know is a pointer to our arguments structure. */
  arg_data *arguments = state->input;

  int num;
  switch (key) {
    case 'c':
      num = atoi(arg);
      arguments->code = (num != JFALSE) ? num : JTRUE;
      break;

    case 'N':
      arguments->invert = JTRUE;
      break;

    case ARGP_KEY_ARG:
      if (!arguments->n_args) {
        arguments->args = CALLOC(char, strlen(arg) + 1);
        stpcpy(arguments->args, arg);
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

static arg_data *init_args(void) {
  arg_data *arguments = MALLOC(arg_data);
  arguments->invert = JFALSE;
  arguments->n_args = 0;
  arguments->args = CALLOC(char, 9);
  arguments->code = 1;

  stpcpy(arguments->args, "Confirm?");

  return arguments;
}

void yes_no(arg_data *arguments) {
  prompt(arguments->args, arguments->invert);
  jbool prev = JFALSE;
  char in;
  int code;
  while ((in = getchar())) {
    switch (in) {
      case 'N':
      case 'n':
        code = arguments->code;
        free(arguments->args);
        free(arguments);
        die(code, NULL);

      case 'Y':
      case 'y':
        free(arguments->args);
        free(arguments);
        die(0, NULL);

      case '\n':
      case '\r':
        if (!prev) {
          code = (arguments->invert) ? arguments->code : 0;
          free(arguments->args);
          free(arguments);
          die(code, NULL);
        }
        prompt(arguments->args, arguments->invert);
        prev = JFALSE;
        break;

      default:
        prev = JTRUE;
        break;
    }
  }
}

int main(int argc, char **argv) {
  arg_data *arguments = init_args();
  argp_parse(&argp, argc, argv, 0, 0, arguments);

  yes_no(arguments);

  int code = arguments->code;

  free(arguments->args);
  free(arguments);
  return code;
}

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
