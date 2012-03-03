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

#include <stdio.h>
#include <getopt.h>

void usage(int op){
  switch (op){
    case OP_NONE:
      printf ("usage: cara [--help | --version] <command> [args]\n");
      putchar('\n');
      printf ("commands:\n");
      printf ("  none (so far)");
      putchar('\n'); 
      putchar('\n'); 
      break;
  }
}

static void version(void){
  putchar('\n');
  printf ("   Cara v%s\n", VERSION);
  //putchar ('\n');
  printf ("   Copyright (c) 2012 by Szymon Urbaś <urbas@hush.ai>\n");
  putchar('\n');
  printf ("   This program is licensed under the MIT license.\n");
  putchar('\n');
}

int main(int argc, char* argv[]){
  if (argc < 2){
    usage(OP_NONE);
    return 1;
  }

  int c;
  while (1){
    static struct option long_options[] = {
      {"version", no_argument, 0, 'v'},
      {"help", no_argument, 0, 'h'},
      {0, 0, 0, 0}
    };

    int option_index = 0;

    c = getopt_long(argc, argv, "vh", long_options, &option_index);

    if (c == -1) break;

    switch (c){
      case 'v':
        version();
        return 0;
        break;
      case 'h':
        usage(OP_NONE);
        return 0;
        break;
      default:
        usage(OP_NONE);
        return 0;
    }
  }

  return 0;
}

