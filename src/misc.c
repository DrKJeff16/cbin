#include <argp.h>
#include <jeff/jeff.h>

const char *argp_program_version = "misc 0.1";
const char *argp_program_bug_address = "<g.maxc.fox@protonmail.com>";
static char doc[] = "Misc test program.";
static char args_doc[] = "[-v] [<ARG>]";
static argp_option_t options[] = { { "verbose", 'v', 0, 0, "Produce verbose output", 0 } };

typedef struct arguments {
  jbool verbose;
  size_t n_args;
} arg_data;

static error_t parse_opt(int key, char *arg, argp_state_t *state) {
  arg_data *arguments = state->input;
  int num_in;
  switch (key) {
    case 'v':
      arguments->verbose = JTRUE;
      break;

    case ARGP_KEY_ARG:
    case ARGP_KEY_END:
      break;

    default:
      return ARGP_ERR_UNKNOWN;
  }
  return 0;
}

static arg_data *init_args(void) {
  arg_data *arguments = MALLOC(arg_data);
  arguments->verbose = JFALSE;
  arguments->n_args = 0;

  return arguments;
}

static argp_t argp = { options, parse_opt, args_doc, doc, NULL, NULL, NULL };

int main(int argc, char **argv) {
  arg_data *arguments = init_args();
  argp_parse(&argp, argc, argv, 0, 0, arguments);

  free(arguments);
  die(0, NULL);
}

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
