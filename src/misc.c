#include <argp.h>
#include <jeff/jeff.h>

const char *argp_program_version = "countdown 0.1";
const char *argp_program_bug_address = "<g.maxc.fox@protonmail.com>";
static char doc[] = "Customizable countdown program.";
static char args_doc[] = "[-v] [-n INT] [-d INT] [<MSG>]";
static argp_option_t options[] = {
  {
    .name = "verbose",
    .key = 'v',
    .arg = 0,
    .flags = 0,
    .doc = "Produce verbose output",
  },
  { 0 },
};

typedef struct arguments {
  jbool verbose;
  size_t n_args;
  char **msg;
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
      if (null_ptr(arguments->msg)) {
        arguments->msg = MALLOC(char *);
        arguments->msg[0] = arg;
        break;
      }
      arguments->msg = REALLOC(arguments->msg, char *, arguments->n_args);
      arguments->msg[arguments->n_args - 1] = arg;
      break;

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
  arguments->msg = MALLOC(char *);
  arguments->msg[0] = MALLOC(char);
  arguments->msg[0][0] = 0;

  return arguments;
}

static argp_t argp = { options, parse_opt, args_doc, doc, NULL, NULL, NULL };

int main(int argc, char **argv) {
  arg_data *arguments = init_args();
  argp_parse(&argp, argc, argv, 0, 0, arguments);

  free(arguments->msg);
  free(arguments);
  die(0, NULL);
}

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
