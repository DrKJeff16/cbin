#include <argp.h>
#include <jeff/jdie.h>
#include <jeff/jmemory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "jeff/jtypes.h"

const char *argp_program_version = "misc 0.1";
const char *argp_program_bug_address = "<g.maxc.fox@protonmail.com>";
static char doc[] = "Misc test program.";
static char args_doc[] = "[-v] [<ARG>]";
static argp_option_t options[] = {
  { "verbose", 'v', 0, 0, "Produce verbose output", 0 },
  { 0 },
};

typedef struct arguments {
  jbool verbose;
  size_t n_args;
  char **args;
} arg_data;

static error_t parse_opt(int key, char *arg, argp_state_t *state) {
  arg_data *arguments = state->input;
  int num_in;
  switch (key) {
    case 'v':
      arguments->verbose = JTRUE;
      break;

    case ARGP_KEY_ARG:
      arguments->n_args++;
      if (null_ptr(arguments->args)) {
        arguments->args = MALLOC(char *);
      } else {
        arguments->args = REALLOC(arguments->args, char *, arguments->n_args);
      }

      arguments->args[arguments->n_args - 1] = CALLOC(char, strlen(arg) + 1);
      stpcpy(arguments->args[arguments->n_args - 1], arg);
      break;

    case ARGP_KEY_END:
      break;

    default:
      return ARGP_ERR_UNKNOWN;
  }
  return 0;
}

static arg_data init_args(void) {
  arg_data arguments = {
    .verbose = JFALSE,
    .n_args = 0,
    .args = NULL,
  };

  return arguments;
}

static argp_t argp = { options, parse_opt, args_doc, doc, NULL, NULL, NULL };

int main(int argc, char **argv) {
  arg_data arguments = init_args();
  argp_parse(&argp, argc, argv, 0, 0, &arguments);

  if (!null_ptr(arguments.args)) {
    size_t i;
    for (i = 0; i < arguments.n_args; i++) {
      printf("%s\n", arguments.args[i]);
      free(arguments.args[i]);
    }
    free(arguments.args);
  }

  die(0, NULL);
}

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
