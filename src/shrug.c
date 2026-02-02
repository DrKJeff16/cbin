#include <argp.h>
#include <jeff/jdie.h>
#include <jeff/jerr.h>
#include <jeff/jmemory.h>
#include <shrug.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum emotions_index {
  FACEPALM,
  FIGHT,
  FUCKYOU,
  LENNY,
  LENNYFIGHT,
  LENNYSHRUG,
  LOVE,
  MEH,
  NERD,
  NICE,
  OMG,
  REALLY,
  SADLENNY,
  SHRUG,
  SMILE,
  THIS,
  TY,
  WOO,
  WTF,
} emotions_idx;

const size_t N_EMOTIONS = 19;

const char *argp_program_version = "shrug 0.1";
const char *argp_program_bug_address = "<g.maxc.fox@protonmail.com>";
static char doc[] = "Print useful ASCII art emotions.";
static char args_doc[] = "[-L] [<EMOTION>]";
static argp_option_t options[] = {
  { "zero", '0', 0, 0, "Terminate with a zero char instead", 0 },
  { "list-emotions", 'L', 0, 0, "List all the available emotions", 1 },
  { 0 },
};

char *emotions(const jbool list_only, const emotions_idx idx) {
  char *emotion = NULL;
  switch (idx) {
    case FACEPALM:
      return (list_only) ? "facepalm" : "(－‸ლ)";
      break;
    case FIGHT:
      return (list_only) ? "fight" : "(ง •̀_•́)ง";
      break;
    case FUCKYOU:
      return (list_only) ? "fuckyou" : "┌П┐(ಠ_ಠ)";
      break;
    case LENNY:
      return (list_only) ? "lenny" : "( ͡° ͜ʖ ͡°)";
      break;
    case LENNYFIGHT:
      return (list_only) ? "lennyfight" : "(ง ͠° ͟ʖ ͡°)ง";
      break;
    case LENNYSHRUG:
      return (list_only) ? "lennyshrug" : "¯\\_( ͡° ͜ʖ ͡°)_/¯";
      break;
    case LOVE:
      return (list_only) ? "love" : "♥‿♥";
      break;
    case MEH:
      return (list_only) ? "meh" : "ಠ_ಠ";
      break;
    case NERD:
      return (list_only) ? "nerd" : "(⌐⊙_⊙)";
      break;
    case NICE:
      return (list_only) ? "nice" : "( ͡° ͜ °)";
      break;
    case OMG:
      return (list_only) ? "omg" : "◕_◕";
      break;
    case REALLY:
      return (list_only) ? "really" : "ò_ô";
      break;
    case SADLENNY:
      return (list_only) ? "sadlenny" : "( ͡° ʖ̯ ͡°)";
      break;
    case SHRUG:
      return (list_only) ? "shrug" : "¯\\_(ツ)_/¯";
      break;
    case SMILE:
      return (list_only) ? "smile" : "ツ";
      break;
    case THIS:
      return (list_only) ? "this" : "( ͡° ͜ʖ ͡°)_/¯";
      break;
    case TY:
      return (list_only) ? "ty" : "\\(^-^)/";
      break;
    case WOO:
      return (list_only) ? "woo" : "＼(＾O＾)／";
      break;
    case WTF:
      return (list_only) ? "wtf" : "(⊙＿⊙')";
      break;

    default:
      return NULL;
  }
}

jbool is_emotion(char *const arg) {
  for (size_t i = 0; i < N_EMOTIONS; i++) {
    if (!strcmp(emotions(JTRUE, i), arg)) {
      return JTRUE;
    }
  }
  return JFALSE;
}

emotions_idx map_emotion(char *const str) {
  emotions_idx i;
  for (i = 0; i < N_EMOTIONS; i++) {
    if (!strcmp(emotions(JTRUE, i), str)) {
      break;
    }
  }

  return i;
}

static error_t parse_opt(int key, char *arg, argp_state_t *state) {
  /* Get the input argument from argp_parse, which we
     know is a pointer to our arguments structure. */
  arg_data *arguments = state->input;

  switch (key) {
    case 'L':
      arguments->list = JTRUE;
      break;

    case ARGP_KEY_ARG:
      if (null_ptr(arguments->args)) {
        arguments->n_args++;
        arguments->args = CALLOC(char, strlen(arg) + 1);
        stpcpy(arguments->args, arg);
      }
      break;

    case ARGP_KEY_END:
      break;

    default:
      return ARGP_ERR_UNKNOWN;
  }
  return 0;
}

static argp_t argp = { options, parse_opt, args_doc, doc, NULL, NULL, NULL };

static arg_data init_args(void) {
  arg_data arguments = {
    .list = JFALSE,
    .n_args = 0,
    .args = NULL,
  };

  return arguments;
}

int main(int argc, char **argv) {
  arg_data arguments = init_args();
  argp_parse(&argp, argc, argv, 0, 0, &arguments);

  if (arguments.list) {
    for (size_t i = 0; i < N_EMOTIONS; i++) {
      printf("%s\n", emotions(JTRUE, i));
    }
    return 0;
  }

  if (null_ptr(arguments.args)) {
    printf("%s\n", emotions(JFALSE, SHRUG));
    return 0;
  }

  if (!is_emotion(arguments.args)) {
    j_err("Not an emotion: `%s`!\n", arguments.args);

    free(arguments.args);
    die(1, NULL);
  }

  printf("%s\n", emotions(JFALSE, map_emotion(arguments.args)));

  free(arguments.args);
  return 0;
}
