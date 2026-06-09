#include <argp.h>
#include <ctype.h>
#include <jeff/jdie.h>
#include <jeff/jmemory.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yn.h>

#include "jeff/jtypes.h"

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
  char *p, *x;
  long num;
  size_t len;
  j_ullong throws;
  jbool digit = JTRUE;

  switch (key) {
    case 'c':
      len = strlen(arg);
      for (x = arg; *x; x++) {
        if (!isdigit(*x)) {
          digit = JFALSE;
          break;
        }
      }

      if (!digit || len == 0) {
        if (!NULL_PTR(arguments->args)) {
          free(arguments->args);
        }
        vdie(1, "Bad argument for `-c`: `%s`\n", arg);
      }

      num = strtol(arg, &p, 10);

      if (num > 239) {
        if (!NULL_PTR(arguments->args)) {
          free(arguments->args);
        }
        vdie(1, "You've exceeded the max shell exit code (`239`): `%ld`\n", num);
      }
      arguments->code = (num != JFALSE) ? num : JTRUE;
      break;

    case 'N':
      arguments->invert = JTRUE;
      break;

    case ARGP_KEY_ARG:
      len = strlen(arg);
      if (!len) {
        break;
      }

      if (NULL_PTR(arguments->args)) {
        arguments->args = CALLOC(char, len + 1);
        stpcpy(arguments->args, arg);
      }
      break;

    case ARGP_KEY_END:
      if (NULL_PTR(arguments->args)) {
        arguments->args = CALLOC(char, 9);
        stpcpy(arguments->args, "Confirm?");
      }
      break;

    default:
      return ARGP_ERR_UNKNOWN;
  }
  return 0;
}

static argp_t argp = { options, parse_opt, args_doc, doc, NULL, NULL, NULL };

static void prompt(char *restrict msg, const jbool negative) {
  printf("%s [%s]: ", msg, (!negative) ? "Y/n" : "y/N");
}

static arg_data init_args(void) {
  arg_data arguments = {
    .invert = JFALSE,
    .args = NULL,
    .code = 1,
  };

  return arguments;
}

static void gc_exit(arg_data *arguments, const int code, char *const msg) {
  free(arguments->args);
  die(code, msg);
}

void yes_no(arg_data *arguments) {
  int code = arguments->code;
  char *args = arguments->args;
  jbool invert = arguments->invert, prev = JFALSE;
  char in;
  prompt(args, invert);
  while ((in = getchar())) {
    switch (in) {
      case 'N':
      case 'n':
        gc_exit(arguments, code, NULL);

      case 'Y':
      case 'y':
        gc_exit(arguments, 0, NULL);

      case '\n':
      case '\r':
        if (!prev) {
          gc_exit(arguments, invert ? code : 0, NULL);
        }
        prompt(args, invert);
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
