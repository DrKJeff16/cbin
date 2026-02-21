#include <argp.h>
#include <jeff/jdie.h>
#include <jeff/jerr.h>
#include <jeff/jmemory.h>
#include <jeff/jstring.h>
#include <shrug.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *argp_program_version = "shrug 0.1";
const char *argp_program_bug_address = "<g.maxc.fox@protonmail.com>";
static char doc[] = "Print useful ASCII art emotions.";
static char args_doc[] = "[-L] [-m] [-0] [<EMOTION>]";
static argp_option_t options[] = {
  { 0, '0', 0, 0, "Terminate with a zero char instead", 0 },
  { 0, 'L', 0, 0, "List all the available emotions", 1 },
  { 0, 'm', 0, 0, "Print the output to support Markdown format", 1 },
  { 0 },
};

char *emotions(const jbool list, const jbool md, const emotions_idx idx) {
  switch (idx) {
    case FACEPALM:
      return (list) ? "facepalm" : "(－‸ლ)";
      break;
    case FIGHT:
      return (list) ? "fight" : "(ง •̀_•́)ง";
      break;
    case FUCKYOU:
      return (list) ? "fuckyou" : "┌П┐(ಠ_ಠ)";
      break;
    case LENNY:
      return (list) ? "lenny" : "( ͡° ͜ʖ ͡°)";
      break;
    case LENNYFIGHT:
      return (list) ? "lennyfight" : "(ง ͠° ͟ʖ ͡°)ง";
      break;
    case LENNYSHRUG:
      return (list) ? "lennyshrug" : ((!md) ? "¯\\_( ͡° ͜ʖ ͡°)_/¯" : "¯\\\\\\_( ͡° ͜ʖ ͡°)\\_/¯");
      break;
    case LOVE:
      return (list) ? "love" : "♥‿♥";
      break;
    case MEH:
      return (list) ? "meh" : "ಠ_ಠ";
      break;
    case NERD:
      return (list) ? "nerd" : "(⌐⊙_⊙)";
      break;
    case NICE:
      return (list) ? "nice" : "( ͡° ͜ °)";
      break;
    case OMG:
      return (list) ? "omg" : "◕_◕";
      break;
    case REALLY:
      return (list) ? "really" : "ò_ô";
      break;
    case SADLENNY:
      return (list) ? "sadlenny" : "( ͡° ʖ̯ ͡°)";
      break;
    case SHRUG:
      return (list) ? "shrug" : ((!md) ? "¯\\_(ツ)_/¯" : "¯\\\\\\_(ツ)\\_/¯");
      break;
    case SMILE:
      return (list) ? "smile" : "ツ";
      break;
    case THIS:
      return (list) ? "this" : ((!md) ? "( ͡° ͜ʖ ͡°)_/¯" : "( ͡° ͜ʖ ͡°)\\_/¯");
      break;
    case TY:
      return (list) ? "ty" : "\\(^-^)/";
      break;
    case WOO:
      return (list) ? "woo" : "＼(＾O＾)／";
      break;
    case WTF:
      return (list) ? "wtf" : "(⊙＿⊙')";
      break;
    default:
      return NULL;
  }
}

jbool is_emotion(char *const arg) {
  for (size_t i = 0; i < N_EMOTIONS; i++) {
    if (!strcmp(emotions(JTRUE, JFALSE, i), arg)) {
      return JTRUE;
    }
  }
  return JFALSE;
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

  if (!null_ptr(arguments->arg)) {
    free(arguments->arg);
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
    case 'L':
      arguments->list = JTRUE;
      break;

    case 'm':
      arguments->md = JTRUE;
      break;

    case '0':
      arguments->zero = JTRUE;
      break;

    case ARGP_KEY_ARG:
      lower_arg = CALLOC(char, strlen(arg) + 1);
      stpcpy(lower_arg, arg);
      lowerize(lower_arg);

      if (!(is_emotion(arg) || is_emotion(lower_arg))) {
        free(lower_arg);
        j_err("Not an emotion: `%s`!\n", arg);
        show_usage(1, arguments);
      }

      use_lower = is_emotion(lower_arg);
      if (null_ptr(arguments->arg)) {
        arguments->arg = CALLOC(char, strlen((use_lower) ? lower_arg : arg) + 1);
        stpcpy(arguments->arg, (use_lower) ? lower_arg : arg);
      }
      free(lower_arg);
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

static arg_data init_args(void) {
  arg_data arguments = { .list = JFALSE, .zero = JFALSE, .md = JFALSE, .arg = NULL };

  return arguments;
}

int main(int argc, char **argv) {
  arg_data arguments = init_args();
  argp_parse(&argp, argc, argv, 0, 0, &arguments);

  if (arguments.list) {
    list_emotions();
  }

  if (null_ptr(arguments.arg)) {
    TO_ZERO(arguments.zero, emotions(JFALSE, arguments.md, SHRUG))
    die(0, NULL);
  }

  if (!is_emotion(arguments.arg)) {
    j_err("Not an emotion: `%s`!\n\n", arguments.arg);
    show_usage(1, &arguments);
  }

  TO_ZERO(arguments.zero, emotions(JFALSE, arguments.md, map_emotion(arguments.arg)))

  free(arguments.arg);
  return 0;
}

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
