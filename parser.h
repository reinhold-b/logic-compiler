/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     DECLARE = 258,
     PREDICATE = 259,
     FUNCTION = 260,
     VARIABLE = 261,
     EXIST = 262,
     ALL = 263,
     TTRUE = 264,
     TFALSE = 265,
     SQUARE_OPEN = 266,
     SQUARE_CLOSE = 267,
     BRACKET_OPEN = 268,
     BRACKET_CLOSE = 269,
     COLON = 270,
     COMMA = 271,
     TILDE = 272,
     SEMICOLON = 273,
     IMPLIES = 274,
     EQUALS = 275,
     OR = 276,
     AND = 277,
     STRING = 278,
     NUMBER = 279
   };
#endif
/* Tokens.  */
#define DECLARE 258
#define PREDICATE 259
#define FUNCTION 260
#define VARIABLE 261
#define EXIST 262
#define ALL 263
#define TTRUE 264
#define TFALSE 265
#define SQUARE_OPEN 266
#define SQUARE_CLOSE 267
#define BRACKET_OPEN 268
#define BRACKET_CLOSE 269
#define COLON 270
#define COMMA 271
#define TILDE 272
#define SEMICOLON 273
#define IMPLIES 274
#define EQUALS 275
#define OR 276
#define AND 277
#define STRING 278
#define NUMBER 279




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 29 "parser.y"
{
	char p[101];
	int num;
	struct Node* n;
	struct SyntaxTree* t;
	struct Node* arg;
}
/* Line 1529 of yacc.c.  */
#line 105 "parser.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

