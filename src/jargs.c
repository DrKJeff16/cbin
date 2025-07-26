#include <argp.h>
#include <stdlib.h>
#include <jeff/jtypes.h>
#include <jeff/jmemory.h>
#include <jeff/jargs.h>

const char *argp_program_version = "jargs v0.0.1";
const char *argp_program_bug_address = "g.maxc.fox@protonmail.com";
static char doc[] = "Description";
static char args_doc[] = "[jargs]...";

const argp_opt_t options[] = {
  { "line", 'l', 0, 0, "Compare lines instead of characters" },
  { "word", 'w', 0, 0, "Compare words instead of characters." },
  { "nocase", 'i', 0, 0, "Compare case insensitive instead of case sensitive." },
  { 0 },
};

static error_t parse_opt(int key, char *arg, struct argp_state *state) {
  argument_t *args = state->input;

  switch (key) {
    case 'l':
      {
        args->mode = LINE_MODE;
        break;
      }
    case 'w':
      {
        args->mode = WORD_MODE;
        break;
      }
    case 'i':
      {
        args->case_sensitive = JFALSE;
        break;
      }
    default:
      return ARGP_ERR_UNKNOWN;
  }

  return 0;
}

int main(int argc, char *argv[]) {
  static struct argp argp = { options, parse_opt, args_doc, doc, 0, 0, 0 };

  argument_t *arguments = MALLOC(argument_t);

  arguments->mode = CHARACTER_MODE;
  arguments->case_sensitive = JTRUE;

  argp_parse(&argp, argc, argv, 0, 0, arguments);

  free(arguments);

  return 0;
}
