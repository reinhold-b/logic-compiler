%{
	#include <stdio.h>
	#include "parser.h"
%}

%option noyywrap

%%
[ \t\n]+    ;  /* Ignore spaces, tabs, and newlines */
\/\*.*?\*\/ {fprintf(stderr, "COMMENT: %s", yytext);};
"DECLARE"	{fprintf(stderr, "KEY: DECLARE\n"); return DECLARE;};
"PREDICATE"	{fprintf(stderr, "KEY: PREDICATE\n"); return PREDICATE;};
"FUNCTION"	{fprintf(stderr, "KEY: FUNCTION\n"); return FUNCTION;};
"VARIABLE"	{fprintf(stderr, "KEY: VARIABLE\n"); return VARIABLE;};
"TRUE"  {fprintf(stderr, "KEY: TRUE\n");return TTRUE;};
"FALSE"  {fprintf(stderr, "KEY: FALSE\n"); return TFALSE;};
";"			{fprintf(stderr, "KEY: SEMICOLON\n"); return SEMICOLON;};
":"			{fprintf(stderr, "KEY: COLON\n"); return COLON;};
","			{fprintf(stderr, "KEY: COMMA\n"); return COMMA;};
"EXIST"		{fprintf(stderr, "KEY: EXIST\n"); return EXIST;};
"ALL"		{fprintf(stderr, "KEY: ALL\n"); return ALL;};
"["			{fprintf(stderr, "KEY: SQUARE OPEN\n"); return SQUARE_OPEN;};
"]"			{fprintf(stderr, "KEY: SQUARE CLOSE\n"); return SQUARE_CLOSE;};
"("			{fprintf(stderr, "KEY: BRACKET OPEN\n"); return BRACKET_OPEN;};
")"			{fprintf(stderr, "KEY: BRACKET CLOSE\n"); return BRACKET_CLOSE;};
"&"			{strcpy(yylval.p, "AND"); fprintf(stderr, "KEY: AND\n"); return AND;};
"|"			{strcpy(yylval.p, "OR"); fprintf(stderr, "KEY: OR\n"); return OR; };
"->"		{strcpy(yylval.p, "IMPLIES"); fprintf(stderr, "KEY: IMPLIES\n"); return IMPLIES;};
"~"			{fprintf(stderr, "KEY: NEGATION\n"); return TILDE;};
"<->"		{strcpy(yylval.p, "EQUALS"); fprintf(stderr, "KEY: EQUIVALENCE"); return EQUALS;};

[0-9]+		{fprintf(stderr, "NUMBER: %d\n", atoi(yytext)); yylval.num=atoi(yytext); return NUMBER;};
([a-zA-Z_][a-zA-Z0-9_]*) {
  	fprintf(stderr, "STRING: %s\n", yytext);
    strncpy(yylval.p, yytext, sizeof(yylval.p) - 1);
    yylval.p[sizeof(yylval.p) - 1] = '\0';
    return STRING;
 }
.			fprintf(stderr, "NOT FOUND\n");

%%