#include <argp.h>
#include <ctype.h>
#include <jeff/jdie.h>
#include <jeff/jerr.h>
#include <jeff/jmemory.h>
#include <jeff/jtypes.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yn.h>

const char *argp_program_version = "yn 1.0";
const char *argp_program_bug_address = "<g.maxc.fox@protonmail.com>";
static char doc[] = "An easy \"Yes/No\" prompt.";
static char args_doc[] = "[-N] [-c CODE] [-t TRIES] [PROMPT [...]]";
static argp_option_t options[] = {
  { "exit-code", 'c', "CODE", 0, "The desired failure exit code", 0 },
  { "invert", 'I', 0, 0, "Invert the default result from pressing `\\n` only", 0 },
  { "num-tries", 't', "TRIES", 0, "Set the maximum amount of tries, set to 0 for unlimited tries (default: `3`)", 0 },
  { 0 },
};

static void gc_exit(arg_data *arguments, const int code) {
  if (!NULL_PTR(arguments->args)) {
    free(arguments->args);
  }
  die(code, NULL);
}

/* Parse a single option. */
static error_t parse_opt(int key, char *arg, argp_state_t *state) {
  /* Get the input argument from argp_parse, which we
     know is a pointer to our arguments structure. */
  arg_data *arguments = state->input;
  char *p;
  long num;
  j_ullong throws;
  jbool digit = JTRUE;

  char *default_msg = "Confirm?";

  switch (key) {
    case 'c':
      for (char *x = arg; *x; x++) {
        if (!isdigit(*x)) {
          digit = JFALSE;
          break;
        }
      }

      if (!digit || strlen(arg) == 0) {
        j_verr("Bad argument for `-c`: `%s`\n", arg);
        gc_exit(arguments, 1);
      }

      num = strtol(arg, &p, 10);

      if (num > YN_MAX_EC) {
        j_verr("You've exceeded the max shell exit code (`%d`): `%ld`\n", YN_MAX_EC, num);
        gc_exit(arguments, 1);
      }
      arguments->code = (num != JFALSE) ? num : JTRUE;
      break;

    case 't':
      for (char *x = arg; *x; x++) {
        if (!isdigit(*x)) {
          digit = JFALSE;
          break;
        }
      }

      if (!digit || strlen(arg) == 0) {
        j_verr("Bad argument for `-t`: `%s`\n", arg);
        gc_exit(arguments, 1);
      }

      num = strtol(arg, &p, 10);

      if (num < 0) {
        j_verr("Invalid number of tries: `%ld`\n", num);
        gc_exit(arguments, 1);
      }
      arguments->tries = (j_ullong)num;
      break;

    case 'I':
      arguments->invert = JTRUE;
      break;

    case ARGP_KEY_ARG:
      if (strlen(arg) != 0) {
        arguments->args =
          (NULL_PTR(arguments->args)) ? MALLOC(char *) : REALLOC(arguments->args, char *, arguments->n_args + 1);
        arguments->args[arguments->n_args] = arg;
        arguments->n_args++;
      }
      break;

    case ARGP_KEY_END:
      if (NULL_PTR(arguments->args)) {
        arguments->args = MALLOC(char *);
        arguments->args[0] = default_msg;
        arguments->n_args = 1;
      }
      break;

    default:
      return ARGP_ERR_UNKNOWN;
  }
  return 0;
}

static argp_t argp = { options, parse_opt, args_doc, doc, NULL, NULL, NULL };

static void prompt(char **restrict msg, const size_t n, const jbool negative) {
  for (size_t i = 0; i < n; i++) {
    printf("%s ", msg[i]);
  }

  printf("[%s]: ", (!negative) ? "Y/n" : "y/N");
}

static arg_data init_args(void) {
  arg_data arguments = {
    .args = NULL,
    .code = 1,
    .invert = JFALSE,
    .n_args = 0,
    .tries = 3,
  };

  return arguments;
}

void yes_no(arg_data *arguments) {
  int code = arguments->code;
  size_t nargs = arguments->n_args;
  j_ullong tries = arguments->tries;
  jbool invert = arguments->invert, prev = JFALSE;
  jbool unlimited_tries = (tries > 0) ? JFALSE : JTRUE;
  char in;

  tries = (unlimited_tries) ? 1 : tries - 1;

  prompt(arguments->args, arguments->n_args, invert);
  while ((in = getchar())) {
    switch (in) {
      case 'N':
      case 'n':
        gc_exit(arguments, code);

      case 'Y':
      case 'y':
        gc_exit(arguments, 0);

      case '\n':
      case '\r':
        if (!prev) {
          gc_exit(arguments, invert ? code : 0);
        }
        if (!(unlimited_tries || tries)) {
          gc_exit(arguments, code);
        }
        if (!unlimited_tries) {
          tries--;
        }
        prompt(arguments->args, arguments->n_args, invert);
        prev = JFALSE;
        break;

      default:
        prev = JTRUE;
        break;
    }
  }
}

static void sig_handler(const int sig) {
  vdie(sig, "Signal caught: %d\n", sig);
}

int main(int argc, char **argv) {
  signal(SIGINT, sig_handler);
  signal(SIGSTOP, sig_handler);
  signal(SIGKILL, sig_handler);
  signal(SIGABRT, sig_handler);
  signal(SIGTERM, sig_handler);
  signal(SIGALRM, sig_handler);
  signal(SIGHUP, sig_handler);
  signal(SIGILL, sig_handler);
  signal(SIGFPE, sig_handler);
  signal(SIGQUIT, sig_handler);
  signal(SIGSEGV, sig_handler);
  signal(SIGTSTP, sig_handler);
  signal(SIGURG, sig_handler);
  signal(SIGVTALRM, sig_handler);
  signal(SIGWINCH, sig_handler);
  signal(SIGXCPU, sig_handler);
  signal(SIGXFSZ, sig_handler);

  arg_data arguments = init_args();
  argp_parse(&argp, argc, argv, 0, 0, &arguments);

  yes_no(&arguments);

  free(arguments.args);
  return arguments.code;
}

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
