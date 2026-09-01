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
static char args_doc[] = "[-v] [-u] [-t THROWS] [-s] [ARG [ARG [...]]]";
static argp_option_t options[] = {
  {
    .arg = 0,
    .doc = "Enable verbose mode",
    .flags = 0,
    .group = 1,
    .key = 'v',
    .name = "verbose",
  },
  {
    .arg = 0,
    .doc = "Use /dev/urandom instead of /dev/random",
    .flags = 0,
    .group = 0,
    .key = 'u',
    .name = "use-urandom",
  },
  {
    .arg = 0,
    .doc = "Whether to do a single throw (will ignore `-t`!)",
    .flags = 0,
    .group = 0,
    .key = 's',
    .name = "single",
  },
  {
    .arg = "THROWS",
    .doc = "Throw the dice N times (default: 2500)",
    .flags = 0,
    .group = 1,
    .key = 't',
    .name = "throws",
  },
  { 0 },
};

char **ndice_values(ndice_t *const ndice) {
  char **items = NULL;
  if (!NULL_PTR(ndice) && ndice_len(ndice) != -1) {
    ndice_t *p = ndice_start(ndice);
    if (!NULL_PTR(p)) {
      size_t idx = 0;

      items = CALLOC(char *, ndice_len(ndice));
      while (!NULL_PTR(p)) {
        items[idx] = p->value;
        p = p->next;
        idx++;
      }
    }
  }
  return items;
}

ndice_t *ndice_remove(ndice_t *ndice, const size_t index) {
  ndice_t *res = NULL;
  if (NULL_PTR(ndice) || ndice_len(ndice) == -1 || ndice_len(ndice) - 1 < (j_llong)index) {
    return res;
  }

  ndice_t *p = ndice_start(ndice);
  while (p->idx != index && !NULL_PTR(p)) {
    if (p->idx < index) {
      p = ndice_next(p);
    } else {
      p = ndice_prev(p);
    }
  }
  if (!NULL_PTR(p)) {
    res = p;
    if (!NULL_PTR(p->next)) {
      p->prev->next = p->next;
      p->next->prev = p->prev;

      do {
        p = ndice_next(p);
        p->idx--;
      } while (!NULL_PTR(p->next));
    } else {
      p->prev->next = NULL;
    }

    ndice = p;
  }
  return res;
}

void ndice_fix_indeces(ndice_t *ndice) {
  if (!NULL_PTR(ndice)) {
    ndice_t *p = ndice_start(ndice);
    size_t count = 0;
    while (!NULL_PTR(p)) {
      p->idx = (p->idx != count) ? count : p->idx;
      p = ndice_next(p);
      count++;
    }
  }
}

ndice_t *ndice_start(ndice_t *const ndice) {
  ndice_t *p = NULL;
  if (!NULL_PTR(ndice)) {
    p = ndice;
    while (!NULL_PTR(p->prev)) {
      p = ndice_prev(p);
    }
  }
  return p;
}

ndice_t *ndice_end(ndice_t *const ndice) {
  ndice_t *p = NULL;
  if (!NULL_PTR(ndice)) {
    p = ndice;
    while (!NULL_PTR(p->next)) {
      p = ndice_next(p);
    }
  }
  return p;
}

ndice_t *ndice_prev(ndice_t *const ndice) {
  return (!NULL_PTR(ndice)) ? ndice->prev : NULL;
}

ndice_t *ndice_next(ndice_t *const ndice) {
  return (!NULL_PTR(ndice)) ? ndice->next : NULL;
}

ndice_t *ndice_index(ndice_t *const ndice, const size_t index) {
  ndice_t *p = NULL;
  if (!NULL_PTR(ndice) && ndice_len(ndice) > (j_llong)index) {
    p = (ndice_start(ndice));
    if (!NULL_PTR(p)) {
      while (p->idx != index) {
        p = ndice_next(p);
      }
    }
  }
  return p;
}

ndice_t *new_ndice(ndice_t *const main_ndice, char *const value) {
  ndice_t *ndice = NULL;
  if (NULL_PTR(value)) {
    return ndice;
  }

  if (NULL_PTR(main_ndice)) {
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
  if (NULL_PTR(ndice)) {
    return main_ndice;
  }

  ndice_t *next = MALLOC(ndice_t);
  next->idx = ndice->idx + 1;
  next->n_landings = 0;
  next->prev = ndice;
  next->next = NULL;

  next->value = CALLOC(char, strlen(value) + 1);
  strcpy(next->value, value);

  ndice->next = next;

  return ndice_start(ndice);
}

ndice_t *gen_full_ndice(char *const values) {
  ndice_t *ndice = NULL;
  if (!NULL_PTR(values)) {
    char *sep_str = CALLOC(char, 2);
    sep_str[0] = ' ';
    sep_str[1] = '\0';

    char *p = values, *sep = values;
    while (!NULL_PTR(sep)) {
      strsep(&p, sep_str);
      ndice = new_ndice(ndice, sep);
      sep = p;
    }

    free(sep_str);
  }

  return ndice;
}

j_llong ndice_len(ndice_t *const ndice) {
  j_llong len = -1;
  if (!NULL_PTR(ndice)) {
    len = 0;
    ndice_t *p = ndice_start(ndice);
    while (!NULL_PTR(p)) {
      len++;
      p = ndice_next(p);
    }
  }
  return len;
}

void ndice_reset_count(ndice_t *ndice) {
  if (!NULL_PTR(ndice)) {
    ndice_t *p = ndice_start(ndice);
    if (!NULL_PTR(p)) {
      while (!NULL_PTR(p->next)) {
        p->n_landings = 0;
        p = ndice_next(p);
      }
    }
  }
}

void ndice_throw(ndice_t *ndice, const jbool urandom) {
  if (!NULL_PTR(ndice) && ndice_len(ndice) != -1) {
    int fd = open(urandom ? "/dev/urandom" : "/dev/random", O_RDONLY);
    if (fd >= 0) {
      j_ullong idx = fd_urand(fd, 0, ndice_len(ndice) - 1);
      close(fd);

      ndice_t *index = ndice_index(ndice, idx);
      if (!NULL_PTR(index)) {
        index->n_landings++;
      }
    }
  }
}

ndice_t *ndice_pop(ndice_t *ndice) {
  ndice_t *res = NULL;
  if (!NULL_PTR(ndice) && ndice_len(ndice) != 0) {
    ndice_t *p = ndice_end(ndice);
    if (!NULL_PTR(p)) {
      if (!NULL_PTR(p->prev)) {
        p->prev->next = NULL;
        p->prev = NULL;
      }

      res = MALLOC(ndice_t);
      memcpy(res, p, sizeof(ndice_t));

      res->value = CALLOC(char, strlen(p->value) + 1);
      strcpy(res->value, p->value);

      free(p->value);
      free(p);
    }
  }
  return res;
}

void ndice_insert(ndice_t *ndice, ndice_t *const new, const size_t index) {
  if (NULL_PTR(ndice) || NULL_PTR(new) || (j_llong)index >= ndice_len(ndice)) {
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
  if (!NULL_PTR(ndice)) {
    ndice_t *end = ndice_end(ndice);
    if (!NULL_PTR(end)) {
      while (!NULL_PTR(end->prev)) {
        end = ndice_prev(end);
        free(end->next->value);
        free(end->next);
      }
    }
    free(ndice->value);
    free(ndice);
  }
}

static error_t parse_opt(int key, char *arg, argp_state_t *state) {
  ndice_arg_t *args = state->input;
  long throws;
  char *p, *x;
  jbool digit = JTRUE, dup = JFALSE;

  switch (key) {
    case 'v':
      args->verbose = JTRUE;
      break;

    case 'u':
      args->urandom = JTRUE;
      break;

    case 's':
      args->single = JTRUE;
      args->n_throws = 1;
      break;

    case 't':
      if (args->single) {
        args->n_throws = DEFAULT_THROWS;
        break;
      }

      for (x = arg; *x; x++) {
        if (!isdigit(*x)) {
          digit = JFALSE;
          break;
        }
      }

      if (!digit || strlen(arg) == 0) {
        if (!NULL_PTR(args->args)) {
          free(args->args);
        }
        vdie(1, "Invalid: `%s`\n", arg);
      }

      throws = strtol(arg, &p, 10);
      if (*p != 0 || p == arg || throws <= 0) {
        if (!NULL_PTR(args->args)) {
          free(args->args);
        }
        die(1, NULL);
      }

      args->n_throws = (j_ullong)throws;
      break;

    case ARGP_KEY_ARG:

      for (size_t i = 0; i < args->n_args; i++) {
        if (strcmp(args->args[args->n_args - 1], arg) == 0) {
          dup = JTRUE;
          break;
        }
      }

      if (!dup) {
        args->n_args++;
        args->args = (args->n_args == 1) ? MALLOC(char *) : REALLOC(args->args, char *, args->n_args);
        args->args[args->n_args - 1] = arg;
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

static ndice_arg_t init_args(void) {
  ndice_arg_t arguments = {
    .args = NULL,
    .n_args = 0,
    .n_throws = DEFAULT_THROWS,
    .single = JFALSE,
    .urandom = JTRUE,
    .verbose = JFALSE,
  };

  return arguments;
}

int main(int argc, char **argv) {
  ndice_arg_t arguments = init_args();
  argp_parse(&argp, argc, argv, 0, 0, &arguments);

  char *value = NULL;
  if (arguments.n_args > 0) {
    for (size_t i = 0; i < arguments.n_args; i++) {
      char *mid = CALLOC(char, strlen(arguments.args[i]) + ((i < arguments.n_args - 1) ? 2 : 1));
      strcpy(mid, arguments.args[i]);

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
    strcpy(value, "1 2 3 4 5 6");
  }

  ndice_t *ndice = gen_full_ndice(value);

  free(value);
  free(arguments.args);

  int fd = open(arguments.urandom ? "/dev/urandom" : "/dev/random", O_RDONLY);
  if (fd < 0) {
    ndice_wipe(ndice);
    j_errno_vdie(1, ENOENT, "`%s` is unavailable\n", arguments.urandom ? "/dev/urandom" : "/dev/random");
  }

  close(fd);

  for (j_ullong i = 0; i < arguments.n_throws; i++) {
    ndice_throw(ndice, arguments.urandom);
  }

  ndice_t *p = ndice_start(ndice), *res = NULL;
  while (!NULL_PTR(p)) {
    printf("%s  ===>  %llu\n", p->value, p->n_landings);
    if (NULL_PTR(res) || p->n_landings > res->n_landings) {
      res = p;
    }
    p = ndice_next(p);
  }

  printf("Length: %lld\tValue: %s\n", ndice_len(res), res->value);

  ndice_wipe(ndice);
  return 0;
}

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
