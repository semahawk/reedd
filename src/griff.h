/*
 * griff.h
 *
 * Copyright: 2012 by Szymon Urbaś <urbas@hush.ai>
 */

#ifndef GRIFF_H
#define GRIFF_H

#define ARRAY_SIZE(x) (sizeof(x) / sizeof *(x))

struct cmd_struct {
  const char* cmd;
  int (*function)(int argc, char** argv, const char* progname);
};

struct pkg_struct {
  char* name;
  char* version;
};

void usage(const char* progname);
void help(const char* progname);
void version(void);

#endif /* GRIFF_H */

