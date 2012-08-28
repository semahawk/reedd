/*
 * reedd.c
 *
 * Copyright: 2012 Szymon Urbaś <urbas@hush.ai>
 *
 * License: (the MIT license)
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <stdio.h>
#include <string.h>

#include "reedd.h"
#include "cmd.h"
#include "config.h"

int main(int argc, char* argv[]){
  /* original program's name */
  const char* progname = argv[0];
  /* initialize the config checking and data retrieving and blah blah blah */
  config_init();

  /* show help if not specified any args */
  if (argc < 2){
    usage(progname);
    return 1;
  }

  /*
   * These options ought to be passed after the programs name ('reedd')
   * and before the command, as argv[1].
   *
   * Unless it won't work..
   */
  if (!strcmp(argv[1], "-V") || !strcmp(argv[1], "--version")){
    version();
    return 0;
  } else if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")){
    help(progname);
    return 0;
  } else if (!strcmp(argv[1], "-u") || !strcmp(argv[1], "--usage")){
    usage(progname);
    return 0;
    /*
     * yarharhar!
     *
     * we 're checking if the first character of argv[0] and
     * --deadbeef is the same - if it is, that means the
     * previous else-ifs didn't catch that option, so there is
     * obviously no such option.
     */
  } else if (!strncmp(argv[1], "--deadbeef", 1)){
    printf("%s: unknown option ‘%s’\n", progname, argv[1]);
    return 1;
  }

  static struct cmd_struct commands[] = {
    { "installs", cmd_installs },
  };

  /* command to be run */
  static char* cmd;

  cmd = argv[1];

  int i, cmd_found = 1;
  for (i = 0; i < ARRAY_SIZE(commands); i++){
    struct cmd_struct *p = commands + i;
    if (strcmp(p->cmd, cmd)){
      cmd_found = 0;
      continue;
    }

    /* run the command which also ends the script with an
     * appropriate return code
     */
    return p->function(argc,argv, progname);
  }

  if (!cmd_found){
    printf("%s: unknown command ‘%s’\n", progname, cmd);
    return 1;
  }
}

void help(const char* progname){
  printf("Usage: %s [--version] [--help] [--usage]\n", progname);
  printf("             <command> [args]\n");
  printf("\n");
  printf("  A package manager for Red Head.\n");
  printf("\n");
  printf("  Commands:\n");
  printf("  installs                   Install a package (doesn't work, of course)");
  printf("\n\n");
  printf("  Options:\n");
  printf("  -h, --help                 Print this help\n");
  printf("  -u, --usage                Output usage info\n");
  printf("  -V, --version              Show version\n");
  printf("\n\n");
  printf("This program is licensed under the MIT license.\n");
  printf("If you have any questions/found a bug, write to <urbas@hush.ai>\n");
}

void usage(const char* progname){
  printf("usage: %s [option] [--help] <command> [args]\n", progname);
}

void version(void){
  printf("\n");
  printf("   Reedd v%s\n", VERSION);
  printf("   Copyright (c) 2012 by Szymon Urbaś <urbas@hush.ai>\n");
  printf("\n");
  printf("   This program is licensed under the MIT license.\n");
  printf("\n");
}

