#include <argp.h>
#include <fcntl.h>
#include <jeff/jdie.h>
#include <jeff/jerr.h>
#include <jeff/jmemory.h>
#include <jeff/jrandom.h>
#include <jeff/jstring.h>
#include <jeff/jtypes.h>
#include <shrug.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *argp_program_version = "shrug 0.1";
const char *argp_program_bug_address = "<g.maxc.fox@protonmail.com>";
static char doc[] = "Print useful ASCII art emotions.";
static char args_doc[] = "[-l] [-m] [-r] [-z] [<EMOTION>]";
static argp_option_t options[] = {
  { "list", 'l', 0, 0, "List all the available emotions", 1 },
  { "markdown", 'm', 0, 0, "Print the output to support Markdown format", 1 },
  { "random", 'r', 0, 0, "Print a random emotion", 0 },
  { "zero", 'z', 0, 0, "Terminate with a zero char instead", 0 },
  { 0 },
};

char *emotions(const jbool list, const jbool md, const emotions_idx idx) {
  char *emotion;
  switch (idx) {
    case FACEPALM:
      emotion = (list) ? "facepalm" : "(－‸ლ)";
      break;
    case FIGHT:
      emotion = (list) ? "fight" : "(ง •̀_•́)ง";
      break;
    case FUCKYOU:
      emotion = (list) ? "fuckyou" : "┌П┐(ಠ_ಠ)";
      break;
    case LENNY:
      emotion = (list) ? "lenny" : "( ͡° ͜ʖ ͡°)";
      break;
    case LENNYFIGHT:
      emotion = (list) ? "lennyfight" : "(ง ͠° ͟ʖ ͡°)ง";
      break;
    case LENNYSHRUG:
      emotion = (list) ? "lennyshrug" : ((!md) ? "¯\\_( ͡° ͜ʖ ͡°)_/¯" : "¯\\\\\\_( ͡° ͜ʖ ͡°)\\_/¯");
      break;
    case LOVE:
      emotion = (list) ? "love" : "♥‿♥";
      break;
    case MEH:
      emotion = (list) ? "meh" : "ಠ_ಠ";
      break;
    case NERD:
      emotion = (list) ? "nerd" : "(⌐⊙_⊙)";
      break;
    case NICE:
      emotion = (list) ? "nice" : "( ͡° ͜ °)";
      break;
    case OMG:
      emotion = (list) ? "omg" : "◕_◕";
      break;
    case REALLY:
      emotion = (list) ? "really" : "ò_ô";
      break;
    case SADLENNY:
      emotion = (list) ? "sadlenny" : "( ͡° ʖ̯ ͡°)";
      break;
    case SHRUG:
      emotion = (list) ? "shrug" : ((!md) ? "¯\\_(ツ)_/¯" : "¯\\\\\\_(ツ)\\_/¯");
      break;
    case SMILE:
      emotion = (list) ? "smile" : "ツ";
      break;
    case THIS:
      emotion = (list) ? "this" : ((!md) ? "( ͡° ͜ʖ ͡°)_/¯" : "( ͡° ͜ʖ ͡°)\\_/¯");
      break;
    case TY:
      emotion = (list) ? "ty" : "\\(^-^)/";
      break;
    case WOO:
      emotion = (list) ? "woo" : "＼(＾O＾)／";
      break;
    case WTF:
      emotion = (list) ? "wtf" : "(⊙＿⊙')";
      break;
    default:
      emotion = NULL;
      break;
  }
  return emotion;
}

jbool is_emotion(char *const arg) {
  jbool res = JFALSE;
  for (size_t i = 0; i < N_EMOTIONS; i++) {
    if (!strcmp(emotions(JTRUE, JFALSE, i), arg)) {
      res = JTRUE;
      break;
    }
  }
  return res;
}

emotions_idx map_emotion(char *const str) {
  emotions_idx i;
  for (i = 0; i < N_EMOTIONS; i++) {
    if (!strcmp(emotions(JTRUE, JFALSE, i), str)) {
      break;
    }
  }

  return i;
}

static void show_usage(const int code, arg_data *arguments) {
  size_t start_spaces = 3;
  size_t len = N_EMOTIONS + start_spaces;

  char **txt = CALLOC(char *, len);
  txt[0] = "Usage: shrug [-L] [-0] [-m] [<EMOTION>]";
  txt[1] = "";
  txt[2] = "Available emotions:";

  size_t i = start_spaces;
  for (i = start_spaces; i < len; i++) {
    txt[i] = emotions(JTRUE, JFALSE, i - start_spaces);
  }

  FILE *stream = (!code) ? stdout : stderr;
  for (i = 0; i < len; i++) {
    fprintf(stream, (i < start_spaces) ? "%s\n" : "   %s\n", txt[i]);
  }

  if (!NULL_PTR(arguments->args)) {
    free(arguments->args);
  }
  free(txt);
  die(code, NULL);
}

static error_t parse_opt(int key, char *arg, argp_state_t *state) {
  /* Get the input argument from argp_parse, which we
     know is a pointer to our arguments structure. */
  arg_data *arguments = state->input;
  char *lower_arg;
  jbool use_lower = JFALSE;

  switch (key) {
    case 'l':
      arguments->list = JTRUE;
      break;

    case 'm':
      arguments->md = JTRUE;
      break;

    case 'r':
      arguments->random = JTRUE;
      break;

    case 'z':
      arguments->zero = JTRUE;
      break;

    case ARGP_KEY_ARG:
      lowerize(arg);

      if (!(is_emotion(arg))) {
        j_err("Not an emotion: `%s`!\n", arg);
        show_usage(1, arguments);
      }

      arguments->n_args++;

      if (NULL_PTR(arguments->args)) {
        arguments->args = MALLOC(char *);
      } else {
        arguments->args = REALLOC(arguments->args, char *, arguments->n_args);
      }

      arguments->args[arguments->n_args - 1] = arg;
      break;

    case ARGP_KEY_END:
      break;

    default:
      return ARGP_ERR_UNKNOWN;
  }
  return 0;
}

static argp_t argp = { options, parse_opt, args_doc, doc, NULL, NULL, NULL };

void list_emotions(void) {
  for (size_t i = 0; i < N_EMOTIONS; i++) {
    printf("%s\n", emotions(JTRUE, JFALSE, i));
  }
  die(0, NULL);
}

void random_emotion(arg_data *arguments) {
  int fd;
  if ((fd = open("/dev/urandom", O_RDONLY)) < 0) {
    die(0, NULL);
  }

  TO_ZERO(arguments->zero, emotions(JFALSE, arguments->md, fd_urand(fd, FACEPALM, WTF)));

  if (!NULL_PTR(arguments->args)) {
    free(arguments->args);
  }
  die(0, NULL);
}

static arg_data init_args(void) {
  arg_data arguments = {
    .list = JFALSE,
    .zero = JFALSE,
    .md = JFALSE,
    .random = JFALSE,
    .n_args = 0,
    .args = NULL,
  };
  return arguments;
}

int main(int argc, char **argv) {
  arg_data arguments = init_args();
  argp_parse(&argp, argc, argv, 0, 0, &arguments);

  if (arguments.list) {
    list_emotions();
  }

  if (arguments.random) {
    random_emotion(&arguments);
  }

  if (NULL_PTR(arguments.args)) {
    TO_ZERO(arguments.zero, emotions(JFALSE, arguments.md, SHRUG))
    die(0, NULL);
  }

  for (size_t i = 0; i < arguments.n_args; i++) {
    if (!is_emotion(arguments.args[i])) {
      j_err("Not an emotion: `%s`!\n\n", arguments.args[i]);
      free(arguments.args);
      show_usage(1, &arguments);
    }

    TO_ZERO(arguments.zero, emotions(JFALSE, arguments.md, map_emotion(arguments.args[i])))
  }

  free(arguments.args);
  return 0;
}

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
