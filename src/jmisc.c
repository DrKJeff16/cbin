#include <argp.h>
#include <iniparser/dictionary.h>
#include <iniparser/iniparser.h>
#include <jeff/jmemory.h>
#include <jeff/jtypes.h>
#include <jmisc.h>
#include <stdio.h>
#include <stdlib.h>

const char *argp_program_version = "jmisc 0.1";
const char *argp_program_bug_address = "<g.maxc.fox@protonmail.com>";
static char doc[] = "Misc test program.";
static char args_doc[] = "[<ARG>]";
static argp_option_t options[] = {
  { 0 },
};

static error_t parse_opt(int key, char *arg, argp_state_t *state) {
  arg_data_t *args = state->input;
  switch (key) {
    case ARGP_KEY_ARG:
      args->n_args++;
      args->args = (NULL_PTR(args->args)) ? MALLOC(char *) : REALLOC(args->args, char *, args->n_args);
      args->args[args->n_args - 1] = arg;
      break;

    case ARGP_KEY_END:
      break;

    default:
      return ARGP_ERR_UNKNOWN;
  }
  return 0;
}

static arg_data_t init_args(void) {
  arg_data_t arguments = {
    .n_args = 0,
    .args = NULL,
  };

  return arguments;
}

static argp_t argp = { options, parse_opt, args_doc, doc, NULL, NULL, NULL };

void ini_file_get(char *const file_name) {
  if (NULL_PTR(file_name)) {
    return;
  }

  dictionary *ini = iniparser_load(file_name);
  if (NULL_PTR(ini)) {
    return;
  }

  const char *gf = iniparser_getstring(ini, "Jeff:girlfriend", "Dan");
  printf("%s\n", gf);

  if (iniparser_find_entry(ini, "Jeff:country") < 0) {
    iniparser_set(ini, "Jeff", NULL);
    iniparser_set(ini, "Jeff:girlfriend", gf);
    iniparser_set(ini, "Jeff:country", "Mexico");

    FILE *ini_file = fopen(file_name, "w+");
    if (!NULL_PTR(ini_file)) {
      iniparser_dump_ini(ini, ini_file);
      fclose(ini_file);
    }
  }

  iniparser_freedict(ini);
}

int main(int argc, char **argv) {
  arg_data_t arguments = init_args();
  argp_parse(&argp, argc, argv, 0, 0, &arguments);

  if (!NULL_PTR(arguments.args)) {
    for (size_t i = 0; i < arguments.n_args; i++) {
      printf("%s\n", arguments.args[i]);
    }

    free(arguments.args);
  }

  char *env_vars[2] = { "FOO", "BAR" };
  for (size_t i = 0; i < 2; i++) {
    char *envvar = secure_getenv(env_vars[i]);
    if (!NULL_PTR(envvar)) {
      printf("%s: %s\n", env_vars[i], envvar);
    }
  }

  ini_file_get("example.ini");

  return 0;
}

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
