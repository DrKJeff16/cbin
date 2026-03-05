#include <argp.h>
#include <jeff/jmemory.h>
#include <jeff/jtypes.h>
#include <ndice.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *argp_program_version = "ndice 0.0.1";
const char *argp_program_bug_address = "<g.maxc.fox@protonmail.com>";
static char doc[] = "N-dice program.";
static char args_doc[] = "[-u]";
static argp_option_t options[] = {
  { 0, 'u', 0, 0, "Use /dev/urandom instead of /dev/random", 1 },
  { 0 },
};

ndice_t *ndice_start(ndice_t *const ndice) {
  if (null_ptr(ndice)) {
    return NULL;
  }

  ndice_t *p = ndice;
  while (!null_ptr(p->prev)) {
    p = ndice_prev(p);
  }

  return p;
}

ndice_t *ndice_end(ndice_t *const ndice) {
  if (null_ptr(ndice)) {
    return NULL;
  }

  ndice_t *p = ndice;
  while (!null_ptr(p->next)) {
    p = ndice_next(p);
  }

  return p;
}

ndice_t *ndice_prev(ndice_t *const ndice) {
  if (null_ptr(ndice)) {
    return NULL;
  }

  return ndice->prev;
}

ndice_t *ndice_next(ndice_t *const ndice) {
  if (null_ptr(ndice)) {
    return NULL;
  }

  return ndice->next;
}

ndice_t *ndice_index(ndice_t *const ndice, const size_t index) {
  if (null_ptr(ndice) || ndice_len(ndice) <= index) {
    return NULL;
  }

  ndice_t *p = ndice_start(ndice);

  while (p->idx != index) {
    p = ndice_next(p);
  }

  return p;
}

ndice_t *new_ndice(ndice_t *const main_ndice, char *const value) {
  if (null_ptr(value)) {
    return NULL;
  }

  ndice_t *ndice;
  if (null_ptr(main_ndice)) {
    ndice = MALLOC(ndice_t);
    ndice->idx = 0;
    ndice->n_landings = 0;
    ndice->prev = NULL;
    ndice->next = NULL;

    ndice->value = CALLOC(char, strlen(value) + 1);
    strcpy(ndice->value, value);

    return ndice;
  }

  ndice = ndice_end(main_ndice);

  ndice_t *next = MALLOC(ndice_t);
  next->idx = ndice->idx + 1;
  next->n_landings = 0;
  next->prev = ndice;
  next->next = NULL;

  next->value = value;
  next->value = CALLOC(char, strlen(value) + 1);
  strcpy(next->value, value);

  ndice->next = next;

  return ndice_start(ndice);
}

ndice_t *gen_full_ndice(char *const values) {
  if (null_ptr(values)) {
    return NULL;
  }

  char sep_str[2] = " ";
  char *p = values, *sep = values;
  ndice_t *ndice = NULL;
  while (!null_ptr(sep)) {
    strsep(&p, sep_str);
    ndice = new_ndice(ndice, sep);
    sep = p;
  }

  return ndice;
}

size_t ndice_len(ndice_t *ndice) {
  if (null_ptr(ndice)) {
    return 0;
  }

  size_t len = 0;
  ndice_t *p = ndice_start(ndice);
  while (!null_ptr(p)) {
    len++;
    p = ndice_next(p);
  }

  return len;
}

void ndice_reset_count(ndice_t *ndice) {
  if (null_ptr(ndice)) {
    return;
  }

  ndice_t *p = ndice_start(ndice);
  while (!null_ptr(p->next)) {
    p->n_landings = 0;
    p = ndice_next(p);
  }
}

void ndice_wipe(ndice_t *ndice) {
  if (null_ptr(ndice)) {
    return;
  }

  ndice_t *end = ndice_end(ndice);
  while (!null_ptr(end->prev)) {
    end = ndice_prev(end);
    free(end->next->value);
    free(end->next);
  }

  free(ndice->value);
  free(ndice);
}

static error_t parse_opt(int key, char *arg, argp_state_t *state) {
  /* Get the input argument from argp_parse, which we
     know is a pointer to our arguments structure. */
  arg_data *arguments = state->input;

  switch (key) {
    case 'u':
      arguments->urandom = JTRUE;
      break;

    case ARGP_KEY_ARG:
      arguments->n_args++;

      if (arguments->n_args == 1) {
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

static arg_data init_args(void) {
  arg_data arguments = {
    .n_args = 0,
    .urandom = JTRUE,
    .args = NULL,
  };

  return arguments;
}

int main(int argc, char **argv) {
  arg_data arguments = init_args();
  argp_parse(&argp, argc, argv, 0, 0, &arguments);

  char *value = NULL;
  if (arguments.n_args > 0) {
    for (size_t i = 0; i < arguments.n_args; i++) {
      char *mid = CALLOC(char, strlen(arguments.args[i]) + ((i < arguments.n_args - 1) ? 2 : 1));
      strcpy(mid, arguments.args[i]);

      if (i < arguments.n_args - 1) {
        strcat(mid, " ");
      }

      if (!null_ptr(value)) {
        value = REALLOC(value, char, strlen(value) + strlen(mid) + 1);
        strcat(value, mid);
        free(mid);
      } else {
        value = mid;
      }
    }
  } else {
    value = CALLOC(char, 12);
    strcpy(value, "1 2 3 4 5 6");
  }

  ndice_t *ndice = gen_full_ndice(value);

  free(value);
  free(arguments.args);

  ndice_t *p = ndice_start(ndice);
  while (!null_ptr(p)) {
    printf("%zu  ===>  %s\n", p->idx, p->value);
    p = ndice_next(p);
  }

  printf("Length: %zu\n", ndice_len(ndice));

  ndice_wipe(ndice);
  return 0;
}
