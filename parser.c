/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



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




/* Copy the first part of user declarations.  */
#line 1 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symboltable.h"
#include "syntaxtree.h"
#include "generate.h"
#include "optimize.h"


extern FILE *yyin;
// Declare the lexer function
int yylex();
void yyerror(const char *s);

static int quantorCounter = 0;
static int argumentCounter = 0;

// Assuming mkBinaryNode is declared in syntaxtree.h
// Node* mkBinaryNode(Node* left, Node* right, const char* operator);
// Assuming mkUnaryNode, mkQuantorNode, mkPredicateNode, mkFunctionNode,
// mkVariableNode, mkNumberNode, mkTrueNode, mkFalseNode, mkArgNode, mkFcArgNode
// and countArgumentsOfNode are declared in syntaxtree.h
// Assuming freeSyntaxTree is declared in syntaxtree.h
// Assuming clearSymbolTable() is declared in symboltable.h and implemented in symboltable.c



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

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
/* Line 193 of yacc.c.  */
#line 180 "parser.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 193 "parser.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   74

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  25
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  46
/* YYNRULES -- Number of states.  */
#define YYNSTATES  79

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   279

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     8,    12,    13,    16,    19,    22,
      24,    30,    36,    42,    44,    46,    48,    50,    56,    62,
      67,    68,    70,    72,    74,    76,    78,    82,    86,    90,
      94,    98,   103,   105,   107,   111,   113,   117,   119,   123,
     125,   129,   131,   134,   136,   138,   142
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      26,     0,    -1,    27,    -1,    26,    27,    -1,    28,    29,
      18,    -1,    -1,    28,    30,    -1,    28,    31,    -1,    28,
      32,    -1,    40,    -1,     3,     4,    23,    15,    24,    -1,
       3,     6,    23,    15,    23,    -1,     3,     5,    23,    15,
      24,    -1,     9,    -1,    10,    -1,    33,    -1,    34,    -1,
       7,    11,    23,    12,    40,    -1,     8,    11,    23,    12,
      40,    -1,    23,    13,    38,    14,    -1,    -1,    33,    -1,
      34,    -1,    24,    -1,    23,    -1,    39,    -1,    38,    16,
      33,    -1,    38,    16,    34,    -1,    38,    16,    24,    -1,
      38,    16,    23,    -1,    38,    16,    39,    -1,    23,    13,
      38,    14,    -1,    41,    -1,    42,    -1,    41,    20,    42,
      -1,    43,    -1,    42,    19,    43,    -1,    44,    -1,    43,
      21,    44,    -1,    45,    -1,    44,    22,    45,    -1,    46,
      -1,    17,    45,    -1,    37,    -1,    36,    -1,    13,    40,
      14,    -1,    35,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    62,    62,    63,    68,   118,   120,   121,   122,   128,
     133,   140,   148,   155,   161,   167,   168,   171,   186,   204,
     223,   226,   236,   246,   258,   281,   286,   296,   306,   318,
     335,   343,   365,   367,   368,   371,   372,   375,   376,   379,
     380,   383,   384,   387,   388,   389,   390
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "DECLARE", "PREDICATE", "FUNCTION",
  "VARIABLE", "EXIST", "ALL", "TTRUE", "TFALSE", "SQUARE_OPEN",
  "SQUARE_CLOSE", "BRACKET_OPEN", "BRACKET_CLOSE", "COLON", "COMMA",
  "TILDE", "SEMICOLON", "IMPLIES", "EQUALS", "OR", "AND", "STRING",
  "NUMBER", "$accept", "program_list", "program", "declarations",
  "top_level_formula", "pred_dec", "var_dec", "func_dec", "true", "false",
  "boolean", "quantifier", "predicate_call", "predicate_params",
  "function_call", "logical_expression", "equivalence_expression",
  "implication_expression", "or_expression", "and_expression",
  "negated_expression", "primary_expression", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    25,    26,    26,    27,    28,    28,    28,    28,    29,
      30,    31,    32,    33,    34,    35,    35,    36,    36,    37,
      38,    38,    38,    38,    38,    38,    38,    38,    38,    38,
      38,    39,    40,    41,    41,    42,    42,    43,    43,    44,
      44,    45,    45,    46,    46,    46,    46
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     3,     0,     2,     2,     2,     1,
       5,     5,     5,     1,     1,     1,     1,     5,     5,     4,
       0,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     4,     1,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     2,     1,     1,     3,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       5,     5,     2,     0,     1,     3,     0,     0,     0,    13,
      14,     0,     0,     0,     0,     6,     7,     8,    15,    16,
      46,    44,    43,     9,    32,    33,    35,    37,    39,    41,
       0,     0,     0,     0,     0,     0,    42,    20,     4,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    45,    24,
      23,    21,    22,     0,    25,    34,    36,    38,    40,     0,
       0,     0,     0,     0,    20,    19,     0,    10,    12,    11,
      17,    18,     0,    29,    28,    26,    27,    30,    31
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,     3,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    53,    54,    23,    24,    25,    26,    27,
      28,    29
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -37
static const yytype_int8 yypact[] =
{
     -37,     5,   -37,     0,   -37,   -37,    10,    -5,     1,   -37,
     -37,    12,    12,    -2,     6,   -37,   -37,   -37,   -37,   -37,
     -37,   -37,   -37,   -37,    18,    -1,    24,    22,   -37,   -37,
      25,    26,    27,    30,    31,    32,   -37,    17,   -37,    12,
      12,    12,    12,    40,    43,    44,    35,    48,   -37,    49,
     -37,   -37,   -37,    20,   -37,   -37,    24,    22,   -37,    37,
      39,    41,    12,    12,    17,   -37,    33,   -37,   -37,   -37,
     -37,   -37,    23,    49,   -37,   -37,   -37,   -37,   -37
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -37,   -37,    64,   -37,   -37,   -37,   -37,   -37,   -36,   -33,
     -37,   -37,   -37,     2,     3,   -11,   -37,    28,    34,    29,
     -10,   -37
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      35,    51,    36,     6,    52,     4,    33,     7,     8,     9,
      10,    37,    34,    11,    30,    31,    32,    12,    40,     7,
       8,     9,    10,    13,    38,    11,     9,    10,    51,    12,
      75,    52,    58,    76,    65,    13,    66,    78,    39,    66,
      49,    50,     9,    10,    42,    41,    48,    62,    43,    44,
      45,    70,    71,    46,    47,    59,    73,    74,    60,    61,
      63,    67,    64,    68,    69,     5,    72,    55,     0,    77,
      57,     0,     0,     0,    56
};

static const yytype_int8 yycheck[] =
{
      11,    37,    12,     3,    37,     0,    11,     7,     8,     9,
      10,    13,    11,    13,     4,     5,     6,    17,    19,     7,
       8,     9,    10,    23,    18,    13,     9,    10,    64,    17,
      66,    64,    42,    66,    14,    23,    16,    14,    20,    16,
      23,    24,     9,    10,    22,    21,    14,    12,    23,    23,
      23,    62,    63,    23,    23,    15,    23,    24,    15,    15,
      12,    24,    13,    24,    23,     1,    64,    39,    -1,    66,
      41,    -1,    -1,    -1,    40
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    26,    27,    28,     0,    27,     3,     7,     8,     9,
      10,    13,    17,    23,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    40,    41,    42,    43,    44,    45,    46,
       4,     5,     6,    11,    11,    40,    45,    13,    18,    20,
      19,    21,    22,    23,    23,    23,    23,    23,    14,    23,
      24,    33,    34,    38,    39,    42,    43,    44,    45,    15,
      15,    15,    12,    12,    13,    14,    16,    24,    24,    23,
      40,    40,    38,    23,    24,    33,    34,    39,    14
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 4:
#line 68 "parser.y"
    {
		SyntaxTree* tree = malloc(sizeof(SyntaxTree));
		if ((yyvsp[(2) - (3)].n) == NULL) {
			fprintf(stderr, "PAR: No top-level formula found for this program.\n");
			tree->root = NULL;
		} else {
			fprintf(stderr, "PAR: Top-level formula found for this program.\n");
			tree->root = (yyvsp[(2) - (3)].n);	// $2 is the root of the formula tree for this program

			fprintf(stderr, "Initial Parse Tree for Program:\n");
			printTree(tree->root, 0);

			fprintf(stderr, "Starting optimization for Program...\n");

			// Apply optimization passes for this single program's tree
			for (int i = 0; i < 5; i++) { // Increased passes for thoroughness
				tree->root = removeImplicationsAndEquivalences(tree->root);
				printTree(tree->root, 0);
				tree->root = pushNegationsToPredicates(tree->root);
				printTree(tree->root, 0);
				tree->root = removeDoubleNeg(tree->root); // Apply multiple times as negations are pushed
				printTree(tree->root, 0);
				tree->root = evaluateBooleanOperators(tree->root); // Apply multiple times for cascading effects
				// If needed, add toPrenexForm here or after the loop
				// tree->root = toPrenexForm(tree->root);
			}

			fprintf(stderr, "Optimized Tree for Program:\n");
			printTree(tree->root, 0);
			fprintf(stderr, "Starting code generation for Program.\n");
			generateCode(tree->root);

            // Optional: Free the syntax tree for this program if not needed later
            // freeSyntaxTree(tree->root); // Uncomment if you have this function and want to free memory per program
		}
        // Free the SyntaxTree structure itself, but not the nodes if freeSyntaxTree is not used
        // free(tree); // Uncomment if you want to free the tree structure per program

        // Clear the symbol table AFTER processing the program
        // You need to implement clearSymbolTable() in symboltable.c/h
        clearSymbolTable();
        // Reset counters for unique IDs if they should be per-program
        quantorCounter = 0;
        argumentCounter = 0;

        // This rule doesn't return a Node* or SyntaxTree*, it just performs actions.
        // $$ = NULL; // Or some indicator if needed, but usually actions suffice for list elements.
	;}
    break;

  case 10:
#line 133 "parser.y"
    {
		printf("PAR: Predicate Declaration: %s (Arity: %d)\n", (yyvsp[(3) - (5)].p), (yyvsp[(5) - (5)].num));
		addSymEntry((yyvsp[(3) - (5)].p), (yyvsp[(3) - (5)].p), Predicate, (yyvsp[(5) - (5)].num));
	;}
    break;

  case 11:
#line 140 "parser.y"
    { // Assuming variable type is given as string like "int"
		printf("PAR: Variable Declaration: %s : %s\n", (yyvsp[(3) - (5)].p), (yyvsp[(5) - (5)].p));
		// Assuming arity 0 for variables
		addSymEntry((yyvsp[(3) - (5)].p), (yyvsp[(3) - (5)].p), Var, 0); // Store type string if needed, arity is 0 for simple vars
	;}
    break;

  case 12:
#line 148 "parser.y"
    { // Number represents arity
		printf("PAR: Function Declaration: %s (Arity: %d)\n", (yyvsp[(3) - (5)].p), (yyvsp[(5) - (5)].num));
		addSymEntry((yyvsp[(3) - (5)].p), (yyvsp[(3) - (5)].p), Function, (yyvsp[(5) - (5)].num));
	;}
    break;

  case 13:
#line 155 "parser.y"
    {
		fprintf(stderr, "PAR: TRUE\n");
		(yyval.n) = mkTrueNode();
	;}
    break;

  case 14:
#line 161 "parser.y"
    {
		fprintf(stderr, "PAR: FALSE\n"); // Corrected log message
		(yyval.n) = mkFalseNode();
	;}
    break;

  case 17:
#line 171 "parser.y"
    { // Changed back to logical_expression
		printf("PAR: EXIST[%s]\n", (yyvsp[(3) - (5)].p));
		char uniqueId[128];
		// Create a unique identifier for the quantified variable in this scope
		snprintf(uniqueId, sizeof(uniqueId), "%s_%d_q", (yyvsp[(3) - (5)].p), quantorCounter++);
		// Add the quantified variable to the symbol table with its unique ID but original public name
		addSymEntry(uniqueId, (yyvsp[(3) - (5)].p), Q_exists, 0); // Arity 0 for quantified variables
		SymTableEntry* entry = getSymEntry(uniqueId);
		if (!entry) {
			fprintf(stderr, "PAR: Error finding symbol table entry for quantified variable %s\n", uniqueId);
			exit(EXIT_FAILURE);
		}
		fprintf(stderr, "PAR: %s QUANTIFIER (%s)\n", typeToString(entry->type), entry->identifier);
		(yyval.n) = mkQuantorNode(entry, (yyvsp[(5) - (5)].n));
	;}
    break;

  case 18:
#line 186 "parser.y"
    { // Changed back to logical_expression
		printf("PAR: ALL[%s]\n", (yyvsp[(3) - (5)].p));
		char uniqueId[128];
		// Create a unique identifier for the quantified variable in this scope
		snprintf(uniqueId, sizeof(uniqueId), "%s_%d_q", (yyvsp[(3) - (5)].p), quantorCounter++);
		// Add the quantified variable to the symbol table with its unique ID but original public name
		addSymEntry(uniqueId, (yyvsp[(3) - (5)].p), Q_all, 0); // Arity 0 for quantified variables
		SymTableEntry* entry = getSymEntry(uniqueId);
		if (!entry) {
			fprintf(stderr, "PAR: Error finding symbol table entry for quantified variable %s\n", uniqueId);
			exit(EXIT_FAILURE);
		}
		fprintf(stderr, "PAR: %s QUANTIFIER (%s)\n", typeToString(entry->type), entry->identifier);
		(yyval.n) = mkQuantorNode(entry, (yyvsp[(5) - (5)].n));
	;}
    break;

  case 19:
#line 204 "parser.y"
    {
		printf("PAR: Predicate Call: %s\n", (yyvsp[(1) - (4)].p));
		SymTableEntry* entry = getSymEntry((yyvsp[(1) - (4)].p));
		if (!entry || entry->type != Predicate) { // Check if it's declared as a predicate
			fprintf(stderr, "PAR: Error: '%s' is not declared as a predicate.\n", (yyvsp[(1) - (4)].p));
			exit(EXIT_FAILURE);
		}
		fprintf(stderr, "SYT: New pred node: %p\n", (yyvsp[(3) - (4)].arg)); // Pass the Node* directly
		(yyval.n) = mkPredicateNode(entry, (yyvsp[(3) - (4)].arg));

		int givenArgs = countArgumentsOfNode((yyval.n));
		if (givenArgs != entry->arity) {
			fprintf(stderr, "AST: ARITY ERROR: Predicate '%s' (expected %d arguments, got %d)\n", entry->identifier, entry->arity, givenArgs);
			exit(EXIT_FAILURE);
		}
	;}
    break;

  case 20:
#line 223 "parser.y"
    {
		(yyval.arg) = NULL;
	;}
    break;

  case 21:
#line 226 "parser.y"
    {
		// Original logic: create a SymTableEntry for the literal and use mkArgNode
		char uniqueId[128];
		snprintf(uniqueId, sizeof(uniqueId), "TRUE_%d", argumentCounter++);
		addSymEntry(uniqueId, "TRUE", Argument, 0); // Assuming Argument type exists
		SymTableEntry* entry = getSymEntry(uniqueId);
		fprintf(stderr, "SYT: New symtable entry: %s\n", uniqueId);
		(yyval.arg) = mkArgNode(entry, NULL);
		fprintf(stderr, "PAR: Arg: TRUE\n");
	;}
    break;

  case 22:
#line 236 "parser.y"
    {
		// Original logic: create a SymTableEntry for the literal and use mkArgNode
		char uniqueId[128];
		snprintf(uniqueId, sizeof(uniqueId), "FALSE_%d", argumentCounter++);
		addSymEntry(uniqueId, "FALSE", Argument, 0); // Assuming Argument type exists
		SymTableEntry* entry = getSymEntry(uniqueId);
		fprintf(stderr, "SYT: New symtable entry: %s\n", uniqueId);
		(yyval.arg) = mkArgNode(entry, NULL);
		fprintf(stderr, "PAR: Arg: FALSE\n");
	;}
    break;

  case 23:
#line 246 "parser.y"
    {
		// Original logic: create a SymTableEntry for the number and use mkArgNode
		char uniqueId[128];
		char temp[30];
		sprintf(temp, "%d", (yyvsp[(1) - (1)].num));
		snprintf(uniqueId, sizeof(uniqueId), "%d_%d", (yyvsp[(1) - (1)].num), argumentCounter++);
		addSymEntry(uniqueId, temp, Argument, 0); // Assuming Argument type exists
		SymTableEntry* entry = getSymEntry(uniqueId);
		fprintf(stderr, "SYT: New symtable entry: %d\n", (yyvsp[(1) - (1)].num));
		(yyval.arg) = mkArgNode(entry, NULL); // Only one argument, no next
		fprintf(stderr, "PAR: Arg: %d\n", (yyvsp[(1) - (1)].num));
	;}
    break;

  case 24:
#line 258 "parser.y"
    { // This should be a variable or a constant like "Tim"
		// Original logic: get SymTableEntry for the string and use mkArgNode
		SymTableEntry* entry = getSymEntry((yyvsp[(1) - (1)].p));
		// Note: Your original code checked for entry->type != Var here,
		// but based on your comment "i didnt use any var in my previous parser, i save strings as identifiers, eg Tim"
		// and the need to handle constants like "Tim", we assume STRINGs here
		// are looked up in the symbol table and used as arguments via mkArgNode.
		// If "Tim" is declared as a VARIABLE, this will work. If it's just a string literal
		// not in the symbol table, getSymEntry will return NULL, which needs handling.
		if (!entry) {
			// If string is not in symbol table, treat it as a new argument identifier
			char uniqueId[128];
			snprintf(uniqueId, sizeof(uniqueId), "%s_%d", (yyvsp[(1) - (1)].p), argumentCounter++);
			addSymEntry(uniqueId, (yyvsp[(1) - (1)].p), Argument, 0); // Assuming Argument type exists
			entry = getSymEntry(uniqueId); // Retrieve the newly added entry
			fprintf(stderr, "SYT: New symtable entry for string literal: %s\n", uniqueId);
		} else {
			// If string is found, use the existing entry
			fprintf(stderr, "SYT: Found existing symtable entry for string: %s\n", entry->identifier);
		}
		(yyval.arg) = mkArgNode(entry, NULL);
		fprintf(stderr, "PAR: Arg: String '%s'\n", (yyvsp[(1) - (1)].p));
	;}
    break;

  case 25:
#line 281 "parser.y"
    {
		fprintf(stderr, "PAR: Arg: Function Call '%s'\n", (yyvsp[(1) - (1)].n)->types.functionType.symEntry->identifier);
		// Original logic: Using mkFcArgNode for function calls as arguments
		(yyval.arg) = mkFcArgNode((yyvsp[(1) - (1)].n), NULL);	// function node as value, no next arg
	;}
    break;

  case 26:
#line 286 "parser.y"
    {
		// Original logic: create a SymTableEntry for the literal and use mkArgNode in a list
		char uniqueId[128];
		snprintf(uniqueId, sizeof(uniqueId), "TRUE_%d", argumentCounter++);
		addSymEntry(uniqueId, "TRUE", Argument, 0); // Assuming Argument type exists
		SymTableEntry* entry = getSymEntry(uniqueId);
		fprintf(stderr, "SYT: New symtable entry: %s\n", uniqueId);
		(yyval.arg) = mkArgNode(entry, (yyvsp[(1) - (3)].arg)); // New arg goes before $1
		fprintf(stderr, "PAR: Arg: TRUE (followed by previous args)\n");
	;}
    break;

  case 27:
#line 296 "parser.y"
    {
		// Original logic: create a SymTableEntry for the literal and use mkArgNode in a list
		char uniqueId[128];
		snprintf(uniqueId, sizeof(uniqueId), "FALSE_%d", argumentCounter++);
		addSymEntry(uniqueId, "FALSE", Argument, 0); // Assuming Argument type exists
		SymTableEntry* entry = getSymEntry(uniqueId);
		fprintf(stderr, "SYT: New symtable entry: %s\n", uniqueId);
		(yyval.arg) = mkArgNode(entry, (yyvsp[(1) - (3)].arg)); // New arg goes before $1
		fprintf(stderr, "PAR: Arg: FALSE (followed by previous args)\n");
	;}
    break;

  case 28:
#line 306 "parser.y"
    {
		// Original logic: create a SymTableEntry for the number and use mkArgNode in a list
		char uniqueId[128];
		char temp[30];
		sprintf(temp, "%d", (yyvsp[(3) - (3)].num));
		snprintf(uniqueId, sizeof(uniqueId), "%d_%d", (yyvsp[(3) - (3)].num), argumentCounter++);
		addSymEntry(uniqueId, temp, Argument, 0); // Assuming Argument type exists
		SymTableEntry* entry = getSymEntry(uniqueId);
		fprintf(stderr, "SYT: New symtable entry: %d\n", (yyvsp[(3) - (3)].num));
		(yyval.arg) = mkArgNode(entry, (yyvsp[(1) - (3)].arg)); // New arg goes before $1
		fprintf(stderr, "PAR: Arg: %d (followed by previous args)\n");
	;}
    break;

  case 29:
#line 318 "parser.y"
    { // This should be a variable or a constant like "Tim"
		// Original logic: get SymTableEntry for the string and use mkArgNode in a list
		SymTableEntry* entry = getSymEntry((yyvsp[(3) - (3)].p));
		if (!entry) {
			// If string is not in symbol table, treat it as a new argument identifier
			char uniqueId[128];
			snprintf(uniqueId, sizeof(uniqueId), "%s_%d", (yyvsp[(3) - (3)].p), argumentCounter++);
			addSymEntry(uniqueId, (yyvsp[(3) - (3)].p), Argument, 0); // Assuming Argument type exists
			entry = getSymEntry(uniqueId); // Retrieve the newly added entry
			fprintf(stderr, "SYT: New symtable entry for string literal: %s\n", uniqueId);
		} else {
			// If string is found, use the existing entry
			fprintf(stderr, "SYT: Found existing symtable entry for string: %s\n", entry->identifier);
		}
		(yyval.arg) = mkArgNode(entry, (yyvsp[(1) - (3)].arg)); // Build linked list with $1 as next
		fprintf(stderr, "PAR: Arg: String '%s' (followed by previous args)\n");
	;}
    break;

  case 30:
#line 335 "parser.y"
    {
		fprintf(stderr, "PAR: Arg: Function Call '%s' (followed by previous args)\n", (yyvsp[(3) - (3)].n)->types.functionType.symEntry->identifier);
		// Original logic: Using mkFcArgNode for function calls as arguments in a list
		(yyval.arg) = mkFcArgNode((yyvsp[(3) - (3)].n), (yyvsp[(1) - (3)].arg)); // new arg goes before $1
	;}
    break;

  case 31:
#line 343 "parser.y"
    {
		printf("PAR: Function Call: %s\n", (yyvsp[(1) - (4)].p));
		SymTableEntry* entry = getSymEntry((yyvsp[(1) - (4)].p));
		if (!entry || entry->type != Function) { // Check if it's declared as a function
			fprintf(stderr, "PAR: Error: '%s' is not declared as a function.\n", (yyvsp[(1) - (4)].p));
			exit(EXIT_FAILURE);
		}

		fprintf(stderr, "AST: Building function node for '%s'\n", (yyvsp[(1) - (4)].p));
		(yyval.n) = mkFunctionNode(entry, (yyvsp[(3) - (4)].arg));

		// Optional: Check arity for functions
		int givenArgs = countArgumentsOfNode((yyval.n)); // You might need a similar function for function nodes
		if (givenArgs != entry->arity) {
			fprintf(stderr, "AST: ARITY ERROR: Function '%s' (expected %d arguments, got %d)\n", entry->identifier, entry->arity, givenArgs);
			exit(EXIT_FAILURE);
		}
	;}
    break;

  case 34:
#line 368 "parser.y"
    { (yyval.n) = mkBinaryNode((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n), "EQUALS"); ;}
    break;

  case 36:
#line 372 "parser.y"
    { (yyval.n) = mkBinaryNode((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n), "IMPLIES"); ;}
    break;

  case 38:
#line 376 "parser.y"
    { (yyval.n) = mkBinaryNode((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n), "OR"); ;}
    break;

  case 40:
#line 380 "parser.y"
    { (yyval.n) = mkBinaryNode((yyvsp[(1) - (3)].n), (yyvsp[(3) - (3)].n), "AND"); ;}
    break;

  case 42:
#line 384 "parser.y"
    { (yyval.n) = mkUnaryNode((yyvsp[(2) - (2)].n)); ;}
    break;

  case 45:
#line 389 "parser.y"
    { (yyval.n) = (yyvsp[(2) - (3)].n); ;}
    break;


/* Line 1267 of yacc.c.  */
#line 1817 "parser.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 393 "parser.y"


/* Error handling function */
void yyerror(const char *s) {
	fprintf(stderr, "PAR: Error: %s\n", s);
}

/* Main function */
int main(int argc, char **argv) {
	++argv, --argc;	/* skip over program name */

	if (argc > 0) {
		yyin = fopen(argv[0], "r");
		if (!yyin) {
			perror("Fehler beim Öffnen der Eingabedatei");
			return 1;
		}
	} else {
		yyin = stdin;
	}

    // *** NEU: Datei einmalig im Schreibmodus öffnen und Header schreiben ***
    FILE *output_file = fopen("output.pl1", "w");
    if (output_file == NULL) {
        perror("Fehler beim Öffnen der Ausgabedatei für Header");
        if (yyin != stdin) fclose(yyin);
        return 1;
    }
    fprintf(output_file, "/* CREATED BY PL1C */\n\n");
    fclose(output_file);
    // *** Ende NEU ***


	int result = yyparse();
	fprintf(stderr, "Parsing result: %d\n", result); // Log the result of yyparse

	if (yyin != stdin) fclose(yyin);	// Close file if not stdin

	return 0;
}

