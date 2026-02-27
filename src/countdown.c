#include <argp.h>
#include <countdown.h>
#include <jeff/jeff.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const char *argp_program_version = "countdown 0.1";
const char *argp_program_bug_address = "<g.maxc.fox@protonmail.com>";
static char doc[] = "Customizable countdown program.";
static char args_doc[] = "[-v] [-s [-f]] [-n INT] [-d INT] [<MSG>]";
static argp_option_t options[] = {
  { 0, 'v', 0, 0, "Produce verbose output", 0 },
  { 0, 's', 0, 0, "Show the number countdown", 1 },
  { 0, 'n', "NUM", 0, "The starting number", 1 },
  { 0, 'd', "DURATION", 0, "The duration per countdown", 1 },
  { 0, 'f', 0, 0, "Don't flush the output, print each count in a newline (assumes `-s`)", 2 },
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

static error_t parse_opt(int key, char *arg, argp_state_t *state) {
  arg_data *arguments = state->input;
  int num_in;
  switch (key) {
    case 'v':
      arguments->verbose = JTRUE;
      break;

    case 'f':
      arguments->flush = JFALSE;
      break;

    case 's':
      arguments->show = JTRUE;
      break;

    case 'n':
      if ((num_in = atoi(arg)) <= 0) {
        num_in = 5;
      }
      arguments->num = (j_uint)num_in;
      break;

    case 'd':
      if ((num_in = atoi(arg)) <= 0) {
        num_in = 1;
      }
      arguments->duration = (j_uint)num_in;
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

j_uint *gen_range(const j_uint num) {
  j_uint *res = CALLOC(j_uint, num);
  for (j_uint i = 0; i < num; i++) {
    res[i] = num - i;
  }

  return res;
}

void count_down(const j_uint *const range, const j_uint num, const j_uint duration, const jbool show,
                const jbool flush) {
  for (j_uint i = 0; i < num; i++) {
    if (show) {
      if (flush) {
        printf("\r%d", range[i]);
        fflush(stdout);
      } else {
        printf("%d\n", range[i]);
      }
    }
    sleep(duration);
  }
}

static arg_data init_args(void) {
  arg_data arguments = {
    .duration = 1,
    .num = 5,
    .verbose = JFALSE,
    .show = JFALSE,
    .flush = JTRUE,
    .n_args = 0,
    .msg = NULL,
  };

  return arguments;
}

/* Our argp parser. */
static argp_t argp = { options, parse_opt, args_doc, doc, NULL, NULL, NULL };

int main(int argc, char **argv) {
  arg_data arguments = init_args();
  argp_parse(&argp, argc, argv, 0, 0, &arguments);

  char *s = CALLOC(char, 1024);
  snprintf(s, 1024, "Duration: %ds\nStarts at: %d\n", arguments.duration, arguments.num);
  s = REALLOC(s, char, strlen(s) + 1);

  verbose_print(arguments.verbose, s, NULL);
  free(s);

  j_uint *range = gen_range(arguments.num);
  count_down(range, arguments.num, arguments.duration, arguments.show, arguments.flush);
  free(range);

  if (arguments.show && arguments.flush) {
    fflush(stdout);
  }

  if (!null_ptr(arguments.msg)) {
    for (size_t i = 0; i < arguments.n_args; i++) {
      printf("%s%c", arguments.msg[i], (i == arguments.n_args - 1) ? 0 : ' ');
    }
    if (arguments.flush) {
      fflush(stdout);
    } else {
      printf("\n");
    }
    free(arguments.msg);
  }

  return 0;
}

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
