/*
 * cara.c
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

#include "cara.h"
#include "commands.h"

#include <stdio.h>
#include <string.h>

void usage(int op, const char* progname){
  switch (op){
    case CMD_NONE:
      printf ("usage: %s [--help | --version] <command> [args]\n", progname);
      putchar('\n');
      printf ("commands:\n");
      printf ("  installs         install a package");
      printf("\n\n");
      break;
  }
}

void version(void){
  putchar('\n');
  printf ("   Cara v%s\n", VERSION);
  printf ("   Copyright (c) 2012 by Szymon Urbaś <urbas@hush.ai>\n");
  putchar('\n');
  printf ("   This program is licensed under the MIT license.\n");
  putchar('\n');
}

int main(int argc, char* argv[]){
  /* original program's name */
  const char* progname = argv[0];

  /* show help if not specified any args */
  if (argc < 2){
    usage(CMD_NONE, progname);
    return 1;
  }

  /*
   * These options ought to be passed after the programs name ('cara')
   * and before the command, as argv[1].
   *
   * Unless it won't work..
   */
  if (!strcmp(argv[1], "-v") || !strcmp(argv[1], "--version")){
    version();
    return 0;
  } else if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")){
    usage(CMD_NONE, progname);
    return 0;
  }

  static struct cmd_struct commands[] = {
    { "installs", command_installs },
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

    /* run the command */
    return p->function(argc, argv, progname);
  }

  if (!cmd_found){
    printf("%s: unknown command ‘%s’\n", progname, cmd);
    return 1;
  }

  return 0;
}

