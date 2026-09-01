#include <argp.h>
#include <jeff/jdie.h>
#include <jeff/jerr.h>
#include <jeff/jfile.h>
#include <jeff/jmemory.h>
#include <jeff/jtypes.h>
#include <nwl_trim.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

const char *argp_program_version = "nwl_trim 0.1";
const char *argp_program_bug_address = "<g.maxc.fox@protonmail.com>";
static char doc[] = "Simple newline trimming plugin.";
static char args_doc[] = "[-v] [-k NUM]";
static argp_option_t options[] = {
  { "verbose", 'v', 0, 0, "Produce verbose output", 0 },
  { "keep-lines", 'k', "KEEP", 0, "Sets how many empty lines to keep (default: 0)", 1 },
  { 0 },
};

static void vverbose_print(const jbool verbose, FILE *restrict stream, const char *fmt, ...) {
  if (verbose && !NULL_PTR(fmt)) {
    va_list argp;
    va_start(argp, fmt);
    fprintf((NULL_PTR(stream)) ? stdout : stream, fmt, argp);
    va_end(argp);
  }
}

static void files_gc(char **files, const j_ullong n) {
  for (j_ullong i = 0; i < n; i++) {
    free(files[i]);
  }
  free(files);
}

static error_t parse_opt(int key, char *arg, argp_state_t *state) {
  nwltrim_arg_t *args = state->input;
  switch (key) {
    case 'v':
      args->verbose = JTRUE;
      break;

    case 'k':
      args->keep_lines = atoi(arg);
      break;

    case ARGP_KEY_ARG:
      if (!is_file(arg)) {
        files_gc(args->files, args->n_files);
        vdie(1, "`%s` is not a file!\n", arg);
      }

      args->n_files++;
      args->files = REALLOC(args->files, char *, args->n_files);

      args->files[args->n_files - 1] = CALLOC(char, strlen(arg) + 1);
      strcpy(args->files[args->n_files - 1], arg);
      break;

    case ARGP_KEY_END:
      break;

    default:
      return ARGP_ERR_UNKNOWN;
  }
  return 0;
}

static argp_t argp = { options, parse_opt, args_doc, doc, NULL, NULL, NULL };

static nwltrim_arg_t init_args(void) {
  nwltrim_arg_t arguments = {
    .verbose = JFALSE,
    .n_files = 0,
    .keep_lines = 0,
    .files = MALLOC(char *),
  };

  return arguments;
}

int main(int argc, char **argv) {
  nwltrim_arg_t arguments = init_args();

  argp_parse(&argp, argc, argv, 0, 0, &arguments);

  if (!arguments.n_files) {
    free(arguments.files);
    die(1, "No files passed!");
  }

  for (j_ullong i = 0; i < arguments.n_files; i++) {
    FILE *file = fopen(arguments.files[i], "r");
    if (NULL_PTR(file)) {
      j_err("Empty file pointer for `%s`!\n", arguments.files[i]);
      files_gc(arguments.files, arguments.n_files);
      die(1, NULL);
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read_n;
    j_ullong l = 0;
    char **lines = NULL;
    while ((read_n = getline(&line, &len, file) != -1)) {
      lines = (NULL_PTR(lines)) ? MALLOC(char *) : REALLOC(lines, char *, l + 1);
      lines[l] = CALLOC(char, strlen(line) + 1);
      strcpy(lines[l], line);

      l++;
    }

    free(line);
    fclose(file);

    j_ullong n_del = 0;
    for (j_ullong j = l - 1; j > 0; j--) {
      if (strlen(lines[j]) > 1) {
        break;
      }

      n_del++;
    }

    if (!n_del) {
      vverbose_print(arguments.verbose, NULL, "`%s` ==> No trailing newlines\n", arguments.files[i]);
      files_gc(lines, l);
      continue;
    }

    while (n_del > 0 && arguments.keep_lines > 0) {
      n_del--;
      arguments.keep_lines--;
    }

    vverbose_print(arguments.verbose, NULL, "`%s` ==> %zu newlines to be deleted\n", arguments.files[i], n_del);

    l -= n_del;

    char *all_lines = MALLOC(char);
    *all_lines = '\0';

    for (j_ullong j = 0; j < l; j++) {
      size_t all_len = strlen(all_lines) + strlen(lines[j]) + 1;
      char *new_all = CALLOC(char, all_len);
      new_all[0] = '\0';

      strcat(new_all, all_lines);
      strcat(new_all, lines[j]);

      all_lines = REALLOC(all_lines, char, all_len);
      strcpy(all_lines, new_all);
      free(new_all);
    }

    file = fopen(arguments.files[i], "w");
    fwrite(all_lines, sizeof(char), strlen(all_lines), file);

    files_gc(lines, l + n_del);
    fclose(file);
  }

  files_gc(arguments.files, arguments.n_files);
  return 0;
}

/* vim: set ts=2 sts=2 sw=2 et ai si sta: */
