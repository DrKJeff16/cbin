#include <argp.h>
#include <countdown.h>
#include <ctype.h>
#include <jeff/jdie.h>
#include <jeff/jmemory.h>
#include <jeff/jtypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const char *argp_program_version = "countdown 0.1";
const char *argp_program_bug_address = "<g.maxc.fox@protonmail.com>";
static char doc[] = "Customizable countdown program.";
static char args_doc[] = "[-v] [-s [-f]] [-n INT] [-d INT] [<MSG> [...]]";
static argp_option_t options[] = {
  { "separator", 'S', "SEP", 0, "The separator string between positional arguments", 1 },
  { "prompt", 'p', "PROMPT", 0, "The prompt to show when making the countdown (requires `-s` to work)", 1 },
  { "duration", 'd', "DURATION", 0, "The duration per countdown", 1 },
  { "no-flush", 'f', 0, 0, "Don't flush the output, print each count in a newline (assumes `-s`)", 2 },
  { "show", 's', 0, 0, "Show the number countdown", 1 },
  { "start-num", 'n', "NUM", 0, "The starting number", 1 },
  { "verbose", 'v', 0, 0, "Produce verbose output", 0 },
  { 0 },
};

static void verbose_print(const jbool verbose, const char *txt, FILE *restrict stream) {
  if (verbose && !NULL_PTR(txt)) {
    fprintf((NULL_PTR(stream)) ? stdout : stream, "%s\n", txt);
  }
}

static error_t parse_opt(int key, char *arg, argp_state_t *state) {
  countdown_arg_t *args = state->input;
  char *p, *x;
  long num;
  jbool digit = JTRUE;
  switch (key) {
    case 'v':
      args->verbose = JTRUE;
      break;

    case 'p':
      args->prompt = CALLOC(char, strlen(arg) + 1);
      strcpy(args->prompt, arg);
      break;

    case 'f':
      args->flush = JFALSE;
      break;

    case 'S':
      if (!NULL_PTR(args->sep)) {
        free(args->sep);
      }

      args->sep = CALLOC(char, strlen(arg) + 1);
      strcpy(args->sep, arg);
      break;

    case 's':
      args->show = JTRUE;
      break;

    case 'n':
      for (x = arg; *x; x++) {
        if (!isdigit(*x)) {
          digit = JFALSE;
          break;
        }
      }

      if (!digit || strlen(arg) == 0) {
        args_gc(args);
        vdie(1, "Invalid: `%s`\n", arg);
      }

      num = strtol(arg, &p, 10);
      if (num <= 0) {
        args_gc(args);
        vdie(1, "Invalid: `%s`\n", arg);
      }

      args->num = num;
      break;

    case 'd':
      for (x = arg; *x; x++) {
        if (!isdigit(*x)) {
          digit = JFALSE;
          break;
        }
      }

      if (!digit || strlen(arg) == 0) {
        args_gc(args);
        vdie(1, "Invalid: `%s`\n", arg);
        break;
      }

      num = strtol(arg, &p, 10);
      if (num <= 0) {
        num = 1;
      }
      args->duration = num;
      break;

    case ARGP_KEY_ARG:
      args->n_args++;
      args->args = (NULL_PTR(args->args)) ? MALLOC(char *) : REALLOC(args->args, char *, args->n_args);
      args->args[args->n_args - 1] = arg;
      break;

    case ARGP_KEY_END:
      if (NULL_PTR(args->sep)) {
        args->sep = CALLOC(char, 2);
        args->sep[0] = '\n';
        args->sep[1] = 0;
      }
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

void count_down(const j_uint *const range, const j_uint num, const j_uint duration, const jbool show, const jbool flush,
                char *const prompt) {
  for (j_uint i = 0; i < num; i++) {
    if (show && flush) {
      printf("\r%s%c%d", (!NULL_PTR(prompt)) ? prompt : "", (!NULL_PTR(prompt)) ? ' ' : 0, range[i]);
      fflush(stdout);
    } else if (show) {
      printf("%s%c%d\n", (!NULL_PTR(prompt)) ? prompt : "", (!NULL_PTR(prompt)) ? ' ' : 0, range[i]);
    }
    sleep(duration);
  }
}

static countdown_arg_t init_args(void) {
  countdown_arg_t arguments = {
    .args = NULL,
    .duration = 1,
    .flush = JTRUE,
    .n_args = 0,
    .num = 5,
    .prompt = NULL,
    .sep = NULL,
    .show = JFALSE,
    .verbose = JFALSE,
  };

  return arguments;
}

static void args_gc(countdown_arg_t *args) {
  if (!NULL_PTR(args)) {
    if (!NULL_PTR(args->args)) {
      free(args->args);
    }
    if (!NULL_PTR(args->prompt)) {
      free(args->prompt);
    }
    if (!NULL_PTR(args->sep)) {
      free(args->sep);
    }
  }
}

/* Our argp parser. */
static argp_t argp = { options, parse_opt, args_doc, doc, NULL, NULL, NULL };

int main(int argc, char **argv) {
  countdown_arg_t arguments = init_args();
  argp_parse(&argp, argc, argv, 0, 0, &arguments);

  char *s = CALLOC(char, 1024);
  snprintf(s, 1024, "Duration: %ds\nStarts at: %d\n", arguments.duration, arguments.num);
  s = REALLOC(s, char, strlen(s) + 1);

  verbose_print(arguments.verbose, s, NULL);
  free(s);

  j_uint *range = gen_range(arguments.num);
  count_down(range, arguments.num, arguments.duration, arguments.show, arguments.flush, arguments.prompt);
  free(range);

  if (arguments.show && arguments.flush) {
    fflush(stdout);
  }

  if (!NULL_PTR(arguments.args)) {
    for (size_t i = 0; i < arguments.n_args; i++) {
      if (arguments.flush) {
        printf("\r%s%s", arguments.args[i], (i == arguments.n_args - 1) ? "" : arguments.sep);
        fflush(stdout);
      } else {
        printf("%s%s", arguments.args[i], (i == arguments.n_args - 1) ? "" : arguments.sep);
        printf("\n");
      }
    }
  }

  args_gc(&arguments);
  return 0;
}

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
