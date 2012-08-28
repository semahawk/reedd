/*
 * src/config_scanner.l
 *
 * Copyright: (c) 2012 by Szymon Urbaś <szymon.urbas@aol.com>
 */

%option outfile="config.lex.yy.c"
%option nounput
%option noinput

%{

  #include <stdio.h>
  #include <string.h>
  #include "config.y.tab.h"

  void count();
  char *strdup(const char *);

  int linenum = 1;

%}

key          [a-zA-Z_]+
int          [-+]?[0-9]+
float        [-+]?[0-9]*\.[0-9]+
dqstring     \"(\\.|[^\"])*\"
sqstring     \'(\\.|[^\'])*\'
whitespace   [ \t]

%x IN_COMMENT

%%

{key}                      { count(); yylval.string = strdup(yytext); return(KEY); }
{int}                      { count(); yylval.integer = atoi(yytext); return(INTEGER); }
{float}                    { count(); yylval.floating = atof(yytext);
return(FLOATING); }
{dqstring}|{sqstring}      { count(); yylval.string = strdup(yytext); return(STR); }
{whitespace}               { /* ignore whitespace */ }
"\n"                       { count(); ++linenum; return(NEWLINE); }
.                          { /* ignore bad characters */ }

<INITIAL>{
"/*"                     BEGIN (IN_COMMENT);
}
<IN_COMMENT>{
"*/"                     BEGIN(INITIAL);
[^*\n]+                  // eat comment in chunks
"*"                      // eat the lone star
\n                       ++linenum;
}

%%

int yywrap()
{
  return(1);
}

int column = 0;

void count()
{
  int i;

  for (i = 0; yytext[i] != '\0'; i++)
    if (yytext[i] == '\n')
      column = 0;
    else if (yytext[i] == '\t')
      column += 8 - (column % 8);
    else
      column++;
}

char *strdup(const char *p)
{
  char *np = malloc(strlen(p) + 1);

  return np ? strcpy(np, p) : np;
}

