/*
 * config.h
 *
 * Copyright: (c) 2012 by Szymon Urbaś <szymon.urbas@aol.com>
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <unistd.h>
#include <sys/types.h>

extern int yyparse();
extern FILE *yyin;

enum setting_type {
  INT = 0,
  FLOAT = 1,
  STRING = 2
};

struct setting_list {
  char *key;   /* a settings key, eg. CFLAGS */
  void *value; /* a value of the setting, eg. "-march=i686" */
  enum setting_type type;
  struct setting_list *next;
};

struct config_struct {
  FILE  * fp;           /* a pointer to the config file */
  char    fn[256];      /* filename of the config file we're using */
};

/* Fetching an appropriate config file.
 *
 * Where do we look for'em?: (in order)
 *
 *   o  ~/.reedd.conf
 *   o  /etc/reedd.conf
 *
 * @param   void
 * @return  void
 *
 */
extern void  config_init();
extern void  config_add_setting();
extern void *config_get_setting(char *);

#endif /* CONFIG_H */

