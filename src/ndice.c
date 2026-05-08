#include <argp.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <jeff/jdie.h>
#include <jeff/jmemory.h>
#include <jeff/jrandom.h>
#include <jeff/jtypes.h>
#include <ndice.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const j_ullong DEFAULT_THROWS = 2500L;

const char *argp_program_version = "ndice 0.0.1";
const char *argp_program_bug_address = "<g.maxc.fox@protonmail.com>";
static char doc[] = "N-dice program.";
static char args_doc[] = "[-u] [-t THROWS] [-s] [ARG [ARG [...]]]";
static argp_option_t options[] = {
  {
    .name = "use-urandom",
    .key = 'u',
    .arg = 0,
    .flags = 0,
    .doc = "Use /dev/urandom instead of /dev/random",
    .group = 0,
  },
  {
    .name = "single",
    .key = 's',
    .arg = 0,
    .flags = 0,
    .doc = "Whether to do a single throw (will ignore `-t`!)",
    .group = 0,
  },
  {
    .name = "throws",
    .key = 't',
    .arg = "THROWS",
    .flags = 0,
    .doc = "Throw the dice N times (default: 2500)",
    .group = 1,
  },
  { 0 },
};

ndice_t *ndice_start(ndice_t *const ndice) {
  if (NULL_PTR(ndice)) {
    return NULL;
  }

  ndice_t *p = ndice;
  while (!NULL_PTR(p->prev)) {
    p = ndice_prev(p);
  }

  return p;
}

ndice_t *ndice_end(ndice_t *const ndice) {
  if (NULL_PTR(ndice)) {
    return NULL;
  }

  ndice_t *p = ndice;
  while (!NULL_PTR(p->next)) {
    p = ndice_next(p);
  }

  return p;
}

ndice_t *ndice_prev(ndice_t *const ndice) {
  if (NULL_PTR(ndice)) {
    return NULL;
  }

  return ndice->prev;
}

ndice_t *ndice_next(ndice_t *const ndice) {
  if (NULL_PTR(ndice)) {
    return NULL;
  }

  return ndice->next;
}

ndice_t *ndice_index(ndice_t *const ndice, const size_t index) {
  if (NULL_PTR(ndice) || ndice_len(ndice) <= index) {
    return NULL;
  }

  ndice_t *p = ndice_start(ndice);
  if (NULL_PTR(p)) {
    return NULL;
  }

  while (p->idx != index) {
    p = ndice_next(p);
  }

  return p;
}

ndice_t *new_ndice(ndice_t *const main_ndice, char *const value) {
  if (NULL_PTR(value)) {
    return NULL;
  }

  ndice_t *ndice;
  if (NULL_PTR(main_ndice)) {
    ndice = MALLOC(ndice_t);
    ndice->idx = 0;
    ndice->n_landings = 0;
    ndice->prev = NULL;
    ndice->next = NULL;

    ndice->value = CALLOC(char, strlen(value) + 1);
    stpcpy(ndice->value, value);

    return ndice;
  }

  ndice = ndice_end(main_ndice);
  if (NULL_PTR(ndice)) {
    return main_ndice;
  }

  ndice_t *next = MALLOC(ndice_t);
  next->idx = ndice->idx + 1;
  next->n_landings = 0;
  next->prev = ndice;
  next->next = NULL;

  next->value = value;
  next->value = CALLOC(char, strlen(value) + 1);
  stpcpy(next->value, value);

  ndice->next = next;

  return ndice_start(ndice);
}

ndice_t *gen_full_ndice(char *const values) {
  if (NULL_PTR(values)) {
    return NULL;
  }

  char sep_str[2] = " ";
  char *p = values, *sep = values;
  ndice_t *ndice = NULL;
  while (!NULL_PTR(sep)) {
    strsep(&p, sep_str);
    ndice = new_ndice(ndice, sep);
    sep = p;
  }

  return ndice;
}

size_t ndice_len(ndice_t *ndice) {
  if (NULL_PTR(ndice)) {
    return 0;
  }

  size_t len = 0;
  ndice_t *p = ndice_start(ndice);
  while (!NULL_PTR(p)) {
    len++;
    p = ndice_next(p);
  }

  return len;
}

void ndice_reset_count(ndice_t *ndice) {
  if (NULL_PTR(ndice)) {
    return;
  }

  ndice_t *p = ndice_start(ndice);
  if (NULL_PTR(p)) {
    return;
  }

  while (!NULL_PTR(p->next)) {
    p->n_landings = 0;
    p = ndice_next(p);
  }
}

void ndice_throw(ndice_t *ndice, const jbool urandom) {
  int fd;
  if ((fd = open(urandom ? "/dev/urandom" : "/dev/random", O_RDONLY)) < 0) {
    return;
  }

  j_ullong idx = fd_urand(fd, 0, ndice_len(ndice) - 1);
  close(fd);

  ndice_t *index = ndice_index(ndice, idx);
  if (NULL_PTR(index)) {
    return;
  }

  index->n_landings++;
}

ndice_t *ndice_pop(ndice_t *ndice) {
  if (NULL_PTR(ndice) || ndice_len(ndice) == 0) {
    return NULL;
  }

  ndice_t *p = ndice_end(ndice);
  if (NULL_PTR(p)) {
    return NULL;
  }

  if (!NULL_PTR(p->prev)) {
    p->prev->next = NULL;
    p->prev = NULL;
  }

  ndice_t *res = MALLOC(ndice_t);
  memcpy(res, p, sizeof(ndice_t));

  res->value = CALLOC(char, strlen(p->value) + 1);
  stpcpy(res->value, p->value);

  free(p->value);
  free(p);
  return res;
}

void ndice_insert(ndice_t *ndice, ndice_t *const new, const size_t index) {
  if (NULL_PTR(ndice) || NULL_PTR(new) || index >= ndice_len(ndice)) {
    return;
  }

  new->idx = index;

  ndice_t *old = ndice;
  ndice = ndice_index(ndice, index);
  if (NULL_PTR(ndice)) {
    ndice = old;
    return;
  }

  if (!NULL_PTR(ndice->prev)) {
    ndice->prev->next = new;
    new->prev = ndice->prev;
  }
  ndice->prev = new;
  new->next = ndice;

  size_t i = 1;
  while (!NULL_PTR(ndice)) {
    ndice->idx = index + i;
    ndice = ndice_next(ndice);
    i++;
  }

  ndice = old;
}

void ndice_wipe(ndice_t *ndice) {
  if (NULL_PTR(ndice)) {
    return;
  }

  ndice_t *end = ndice_end(ndice);
  if (NULL_PTR(end)) {
    free(ndice->value);
    free(ndice);
    return;
  }
  while (!NULL_PTR(end->prev)) {
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
  long throws;
  char *p, *x;
  jbool digit = JTRUE;

  switch (key) {
    case 'u':
      arguments->urandom = JTRUE;
      break;

    case 's':
      arguments->single = JTRUE;
      arguments->n_throws = 1;
      break;

    case 't':
      if (arguments->single) {
        arguments->n_throws = DEFAULT_THROWS;
        break;
      }

      for (x = arg; *x; x++) {
        if (!isdigit(*x)) {
          digit = JFALSE;
          break;
        }
      }

      if (!digit || strlen(arg) == 0) {
        if (!NULL_PTR(arguments->args)) {
          free(arguments->args);
        }
        vdie(1, "Invalid: `%s`\n", arg);
      }

      throws = strtol(arg, &p, 10);
      if (*p != 0 || p == arg || throws <= 0) {
        if (!NULL_PTR(arguments->args)) {
          free(arguments->args);
        }
        die(1, NULL);
      }

      arguments->n_throws = (j_ullong)throws;
      break;

    case ARGP_KEY_ARG:
      arguments->n_args++;

      arguments->args = (arguments->n_args == 1) ? MALLOC(char *) : REALLOC(arguments->args, char *, arguments->n_args);
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
    .args = NULL,
    .n_args = 0,
    .n_throws = DEFAULT_THROWS,
    .urandom = JTRUE,
    .single = JFALSE,
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
      stpcpy(mid, arguments.args[i]);

      if (i < arguments.n_args - 1) {
        strcat(mid, " ");
      }

      if (!NULL_PTR(value)) {
        value = REALLOC(value, char, strlen(value) + strlen(mid) + 1);
        strcat(value, mid);
        free(mid);
      } else {
        value = mid;
      }
    }
  } else {
    value = CALLOC(char, 12);
    stpcpy(value, "1 2 3 4 5 6");
  }

  ndice_t *ndice = gen_full_ndice(value);

  free(value);
  free(arguments.args);

  int fd;
  if ((fd = open(arguments.urandom ? "/dev/urandom" : "/dev/random", O_RDONLY)) < 0) {
    ndice_wipe(ndice);
    j_errno_vdie(1, ENOENT, "`%s` is unavailable\n", arguments.urandom ? "/dev/urandom" : "/dev/random");
  }

  for (j_ullong i = 0; i < arguments.n_throws; i++) {
    ndice_throw(ndice, arguments.urandom);
  }

  ndice_t *p = ndice_start(ndice);
  ndice_t *res = NULL;
  while (!NULL_PTR(p)) {
    printf("%llu  ===>  %llu\n", p->idx, p->n_landings);
    if (NULL_PTR(res) || p->n_landings > res->n_landings) {
      res = p;
    }
    p = ndice_next(p);
  }

  printf("%llu\n", res->idx);

  ndice_wipe(ndice);
  return 0;
}

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
