#include <argp.h>
#include <jeff/jeff.h>
#include <stdio.h>
#include <string.h>
#include <yn.h>

const char *argp_program_version = "yn 1.0";
const char *argp_program_bug_address = "<g.maxc.fox@protonmail.com>";
static char doc[] = "An easy \"Yes/No\" prompt.";
static char args_doc[] = "[-h] [-N] [<X>]";

static struct argp_option options[] = {
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
struct arguments {
  jbool invert;
  char *args[1];
};

/* Parse a single option. */
static error_t parse_opt(int key, char *arg, struct argp_state *state) {
  /* Get the input argument from argp_parse, which we
     know is a pointer to our arguments structure. */
  struct arguments *arguments = state->input;

  switch (key) {
    case 'N':
      arguments->invert = JTRUE;
      break;

    case ARGP_KEY_ARG:
      arguments->args[state->arg_num] = arg;
      break;

    case ARGP_KEY_END:
      break;

    default:
      return ARGP_ERR_UNKNOWN;
  }
  return 0;
}

static struct argp argp = { options, parse_opt, args_doc, doc, NULL, NULL, NULL };

void prompt(char *msg, const jbool negative) {
  j_rstrip(' ', msg);
  printf("%s [%s]: ", msg, (!negative) ? "Y/n" : "y/N");
}

int main(int argc, char **argv) {
  struct arguments arguments;
  arguments.invert = JFALSE;
  arguments.args[0] = NULL;

  argp_parse(&argp, argc, argv, 0, 0, &arguments);

  char *c = (null_ptr(arguments.args[0])) ? "Confirm?" : arguments.args[0];
  char *msg = CALLOC(char, strlen(c) + 1);
  stpcpy(msg, c);

  prompt(msg, arguments.invert);
  jbool prev = JFALSE;
  char *in = MALLOC(char);

  void **garbage = CALLOC(void *, 2);
  garbage[0] = VOID_PTR(msg);
  garbage[1] = VOID_PTR(in);

  *in = getchar();
  do {
    switch (*in) {
      case 'N':
      case 'n':
        j_gc(garbage, 3);
        return 1;

      case 'Y':
      case 'y':
        j_gc(garbage, 3);
        return 0;

      case '\n':
      case '\r':
        if (!prev) {
          j_gc(garbage, 3);
          return arguments.invert;
        }
        prev = JFALSE;
        prompt(msg, arguments.invert);
        break;

      default:
        prev = JTRUE;
        break;
    }
  } while ((*in = getchar()));

  j_gc(garbage, 3);
  return 127;
}

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
