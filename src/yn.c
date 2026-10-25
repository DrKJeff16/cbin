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
  { "no-yn-prompt", 'n', 0, 0, "If passed, the `[Y/n]` prompt will not appear", 0 },
  { 0 },
};

static void gc_exit(yn_arg_t *args, const int code) {
  if (!NULL_PTR(args->args)) {
    free(args->args);
  }
  die(code, NULL);
}

static error_t parse_opt(int key, char *arg, argp_state_t *state) {
  yn_arg_t *args = state->input;
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
        gc_exit(args, 1);
      }

      num = strtol(arg, &p, 10);

      if (num > YN_MAX_EC) {
        j_verr("You've exceeded the max shell exit code (`%d`): `%ld`\n", YN_MAX_EC, num);
        gc_exit(args, 1);
      }
      args->code = (num != JFALSE) ? num : JTRUE;
      break;

    case 'n':
      args->no_yn = JTRUE;
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
        gc_exit(args, 1);
      }

      num = strtol(arg, &p, 10);

      if (num < 0) {
        j_verr("Invalid number of tries: `%ld`\n", num);
        gc_exit(args, 1);
      }
      args->tries = (j_ullong)num;
      break;

    case 'I':
      args->invert = JTRUE;
      break;

    case ARGP_KEY_ARG:
      if (strlen(arg) != 0) {
        args->args = (NULL_PTR(args->args)) ? MALLOC(char *) : REALLOC(args->args, char *, args->n_args + 1);
        args->args[args->n_args] = arg;
        args->n_args++;
      }
      break;

    case ARGP_KEY_END:
      if (NULL_PTR(args->args)) {
        args->args = MALLOC(char *);
        args->args[0] = default_msg;
        args->n_args = 1;
      }
      break;

    default:
      return ARGP_ERR_UNKNOWN;
  }
  return 0;
}

static argp_t argp = { options, parse_opt, args_doc, doc, NULL, NULL, NULL };

static void prompt(char **restrict msg, const size_t n, const jbool negative, const jbool no_prompt) {
  for (size_t i = 0; i < n; i++) {
    printf("%s", msg[i]);
  }
  if (!no_prompt) {
    printf(" [%s]: ", (!negative) ? "Y/n" : "y/N");
  } else {
    printf(": ");
  }
}

static yn_arg_t init_args(void) {
  yn_arg_t args = {
    .args = NULL,
    .code = 1,
    .invert = JFALSE,
    .n_args = 0,
    .no_yn = JFALSE,
    .tries = 3,
  };

  return args;
}

void yes_no(yn_arg_t *args) {
  int code = args->code;
  size_t nargs = args->n_args;
  j_ullong tries = args->tries;
  jbool invert = args->invert, no_yn = args->no_yn;
  jbool prev = JFALSE, unlimited_tries = (tries > 0) ? JFALSE : JTRUE;
  char in;

  tries = (unlimited_tries) ? 1 : tries - 1;

  prompt(args->args, args->n_args, invert, no_yn);
  while ((in = getchar())) {
    switch (in) {
      case 'N':
      case 'n':
        gc_exit(args, code);

      case 'Y':
      case 'y':
        gc_exit(args, 0);

      case '\n':
      case '\r':
        if (!prev) {
          gc_exit(args, invert ? code : 0);
        }
        if (!(unlimited_tries || tries)) {
          gc_exit(args, code);
        }
        if (!unlimited_tries) {
          tries--;
        }
        prompt(args->args, args->n_args, invert, no_yn);
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
  signal(SIGABRT, sig_handler);
  signal(SIGALRM, sig_handler);
  signal(SIGFPE, sig_handler);
  signal(SIGHUP, sig_handler);
  signal(SIGILL, sig_handler);
  signal(SIGINT, sig_handler);
  signal(SIGKILL, sig_handler);
  signal(SIGQUIT, sig_handler);
  signal(SIGSEGV, sig_handler);
  signal(SIGSTOP, sig_handler);
  signal(SIGTERM, sig_handler);
  signal(SIGTSTP, sig_handler);
  signal(SIGURG, sig_handler);
  signal(SIGVTALRM, sig_handler);
  signal(SIGWINCH, sig_handler);
  signal(SIGXCPU, sig_handler);
  signal(SIGXFSZ, sig_handler);

  yn_arg_t args = init_args();
  argp_parse(&argp, argc, argv, 0, 0, &args);

  yes_no(&args);

  free(args.args);
  return args.code;
}

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
