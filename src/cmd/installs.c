/*
 * cmd/installs.c
 *
 * Copyright: (c) 2012 by Szymon Urbaś <urbas@hush.ai>
 */

#include "reedd.h"
#include "cmd.h"

#include <stdio.h>
#include <argp.h>

const char* argp_program_bug_adress = "<urbas@hush.ai>";
static char doc[] = "\n  Installing packages utility.";
static char args_doc[] = "<package>";

static struct argp_option options[] = {
  { 0, 0, 0, 0, " General options:" },
  { "pkg-version", 'v', "VERSION", 0, "Specify a program's version" },
  { 0, 0, 0, 0, 0 }
};

struct arguments {
  char* args[1];
  struct pkg_struct pkg;
};

static error_t parse_opt(int key, char* arg, struct argp_state* state){
  struct arguments* arguments = state->input;

  switch (key){
    case 'v':
      arguments->pkg.version = arg;
      break;

    case ARGP_KEY_ARG:
      if (state->arg_num >= 2)
        argp_usage(state);
      arguments->args[state->arg_num] = arg;
      break;
    case ARGP_KEY_END:
      if (state->arg_num <= 1)
        argp_usage(state);
      break;
    default:
      return ARGP_ERR_UNKNOWN;
  }

  return 0;
}

static struct argp argp = { options, parse_opt, args_doc, doc };

int cmd_installs(int argc, char* argv[], const char* progname){
  struct arguments arguments;

  /*
   * a little trick
   *
   * we want help to show 'reedd installs [OPTION...] ..'
   * instead of just 'reedd [OPTION...] ..'
   */
  argv[0] = "reedd installs";

  arguments.pkg.name = "null";
  arguments.pkg.version = "newest";

  argp_parse(&argp, argc, argv, ARGP_HELP_BUG_ADDR, 0, &arguments);

  printf("package %s, version: %s\n", arguments.pkg.name, arguments.pkg.version);

  return 0;
}

