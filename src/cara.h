/*
 * cara.h
 *
 * Copyright: 2012 by Szymon Urbaś <urbas@hush.ai>
 */

#ifndef CARA_H
#define CARA_H

//#define VERSION_MAJOR "0"
//#define VERSION_MINOR "1"
//#define VERSION_PATCH "0"
//#define VERSION VERSION_MAJOR "." VERSION_MINOR "." VERSION_PATCH

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

#endif /* CARA_H */

