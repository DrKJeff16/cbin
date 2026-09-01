#include <argp.h>
#include <ini.h>
#include <jeff/jerr.h>
#include <jeff/jmemory.h>
#include <jeff/jstring.h>
#include <jeff/jtypes.h>
#include <jmisc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *argp_program_version = "jmisc 0.1";
const char *argp_program_bug_address = "<g.maxc.fox@protonmail.com>";
static char doc[] = "Misc test program.";
static char args_doc[] = "[<ARG>]";
static argp_option_t options[] = {
  { 0 },
};

static error_t parse_opt(int key, char *arg, argp_state_t *state) {
  jmisc_arg_t *args = state->input;
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

static jmisc_arg_t *init_args(void) {
  jmisc_arg_t *arguments = MALLOC(jmisc_arg_t);
  arguments->n_args = 0;
  arguments->args = NULL;

  return arguments;
}

static argp_t argp = { options, parse_opt, args_doc, doc, NULL, NULL, NULL };

static int j_ini_handler(void *user, const char *section, const char *key, const char *value) {
  config_t *pconfig = (config_t *)user;

  if (J_STRMATCH(section, "protocol") && J_STRMATCH(key, "version")) {
    pconfig->version = atoi(value);
  } else if (J_STRMATCH(section, "user") && J_STRMATCH(key, "name")) {
    pconfig->name = strdup(value);
  } else if (J_STRMATCH(section, "user") && J_STRMATCH(key, "gf")) {
    pconfig->gf = strdup(value);
  } else {
    return 0;
  }
  return 1;
}

int main(int argc, char **argv) {
  jmisc_arg_t *arguments = init_args();
  argp_parse(&argp, argc, argv, 0, 0, arguments);

  if (!NULL_PTR(arguments->args)) {
    for (size_t i = 0; i < arguments->n_args; i++) {
      printf("%s\n", arguments->args[i]);
    }
    free(arguments->args);
  }
  free(arguments);

  char *env_vars[2] = { "FOO", "BAR" };
  for (size_t i = 0; i < 2; i++) {
    char *envvar = secure_getenv(env_vars[i]);
    if (!NULL_PTR(envvar)) {
      printf("%s: %s\n", env_vars[i], envvar);
    }
  }

  config_t config;
  if (ini_parse("example.ini", j_ini_handler, &config) >= 0) {
    printf("example.ini:\nversion ==> %d\nname ==> %s\ngf ==> %s", config.version, config.name, config.gf);
  } else {
    j_err("Can't load example.ini\n", NULL);
  }

  return 0;
}

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
