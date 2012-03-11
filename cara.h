/*
 * cara.h
 *
 * Copyright: 2012 by Szymon Urbaś <urbas@hush.ai>
 */

#ifndef CARA_H
#define CARA_H

#define VERSION "0.1.0"

#define CMD_NONE     0
#define CMD_INSTALLS 1

#define ARRAY_SIZE(x) (sizeof(x) / sizeof *(x))

struct cmd_struct {
  const char* cmd;
  /*              argc argv    progname */
  int (*function)(int, char**, const char*);
};

struct pkg_struct {
  char* name;
  char* version;
};

void usage(int op, const char* progname);
void version(void);

#endif /* CARA_H */

