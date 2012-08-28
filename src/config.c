/*
 * config.c
 *
 * Copyright: (c) 2012 Szymon Urbaś <szymon.urbas@aol.com>
 */

#include "config.h"

extern int yyparse(void);
extern FILE *yyin;
extern FILE *yyout;

struct setting_list *head = NULL;

void config_init()
{
  char buff[256];
  FILE *fp;

  struct passwd *p = getpwuid(getuid());

  snprintf(buff, 256, "%s/.reedd.conf", p->pw_dir);

  if ((fp = fopen(buff, "r")) != NULL){
    /* we can open ~/.reedd.conf, so we use it */
    yyin = fp;
  } else {
    /* can't open ~/.reedd.conf, so we try to open /etc/reedd.conf  */
    if ((fp = fopen("/etc/reedd.conf", "r")) != NULL){
      /* we actually can */
      yyin = fp;
    } else {
      fprintf(stderr, "fatality: no config file found :(\n");
      exit(1);
    }
  }
  
  /* parse through the input until there is no more */
  do {
    yyparse();
  } while (!feof(yyin));
}

void config_add_setting(char *key, void *value, enum setting_type type)
{
  struct setting_list *new_node = malloc(sizeof(struct setting_list));

  if (new_node == NULL){
    fprintf(stderr, "error: malloc failed in add_to_list() at line %d\n", __LINE__);
    exit(EXIT_FAILURE);
  }

  switch (type){
    case STRING:  new_node->value = (char*)value;
                  new_node->type = STRING;
                  break;
    case INT:     new_node->value = (int*)value;
                  new_node->type = INT;
                  break;
    case FLOAT:   new_node->value = (double*)value;
                  new_node->type = FLOAT;
                  break;
    default:      fprintf(stderr, "error: unknown key option\n");
                  exit(EXIT_FAILURE);
  }

  new_node->key  = key;
  new_node->next = head;

  head = new_node;
}

void *config_get_setting(char *key)
{
  struct setting_list *p;

  for (p = head; p != NULL; p = p->next)
    if (!strcmp(key, p->key))
      return (void*)p->value;

  fprintf(stderr, "unknown setting: ‘%s’\n", key);
  exit(1);
}

