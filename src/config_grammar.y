/*
 * src/config_grammar.y
 *
 * Copyright: (c) 2012 by Szymon Urbaś <szymon.urbas@aol.com>
 */

%output="config.y.tab.c"

%{

  #include <stdio.h>
  #include <stdlib.h>
  #include "config.h"

  void yyerror(const char *s);
  int yylex();

  extern int linenum;

%}

%union {
  int    integer;
  double floating;
  char * string;
}

%token NEWLINE

%token <string> KEY STR
%token <floating> FLOATING
%token <integer> INTEGER

%%

config: body
      ;

body: settings
    ;

settings: settings setting
        | setting terminator
        ;

setting: KEY INTEGER    { config_add_setting($1, $2, INT); }
       | KEY FLOATING   { config_add_setting($1, $2, FLOAT); }
       | KEY STR        { config_add_setting($1, $2, STRING); }
       | terminator
       ;

terminator: NEWLINE
          | ';'
          ;

%%

void yyerror(const char *s)
{
  fprintf(stderr, "HOLY MOLY ERRAH: %s at line %d\n", s, linenum);

  exit(1);
}

