
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "Collection.y"

void yyerror (char *s);
int yylex();
#include <stdio.h>     
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "symTab.h"
#include "functions.h"
extern char* yytext;
extern int size;

FILE *outputFile, *inputFile;

//	===	YACC Helper Functions	============================

char* CopyStr(char* str)
{
    char *new, *p;

    if (str[0] == '\"') {           
        new = malloc(strlen(str));
        if ((p = strchr(str+1, '\"')))
            *p = '\0';
        strcpy(new, str);
    }
    else {
        new = malloc(strlen(str)+1);   
        strcpy(new, str);
    }

    return new;
}

char* AddStrToList(char* list, char* str)
{
    char *p;
    char *new = realloc(list, strlen(list)+strlen(str));
    strcat(new, "@");
    if ((p = strchr(str+1, '\"')))
        *p = '\0';
    strcat(new, str+1);
	return new;
}
char *AddToList(char *list, char *str)
{
    char *new = realloc(list, strlen(list) + strlen(str)+2);
    strcat(new, "@");
    strcat(new, str);
    return new;
}
static int idx=0;

void insert(char* varName, varType typ)
{	
    for (int i = 0; i < idx; i++)
    {
        if (strcmp(SymTable[i].name, varName) == 0)
        {
            yyerror("Variable already defined\n");
            return;
        }
    }
	SymTable[idx].name = malloc(strlen(varName)+1);
	strcpy(SymTable[idx].name, varName);
    SymTable[idx].typ = typ;
	++idx;
}

varType getTyp(char* var)
{
    for (int i=0 ; i<idx ; ++i)
        if (strcmp(SymTable[i].name, var)==0)
            return SymTable[i].typ;
    return 0;
}





/* Line 189 of yacc.c  */
#line 156 "Collection.tab.c"

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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     t_STRING = 258,
     t_ID = 259,
     t_INT = 260,
     t_IF_CMD = 261,
     t_ELSE_CMD = 262,
     t_FOR_CMD = 263,
     t_WHILE_CMD = 264,
     t_BIGGER_EQUAL = 265,
     t_LOWER_EQUAL = 266,
     t_EQUAL = 267,
     t_NOT = 268,
     t_COLLECTION_CMD = 269,
     t_SET_CMD = 270,
     t_INT_CMD = 271,
     t_STRING_CMD = 272,
     t_INPUT_CMD = 273,
     t_OUTPUT_CMD = 274,
     t_LOWER = 275,
     t_BIGGER = 276
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 83 "Collection.y"

        struct literal_with_type* literal_struct;
        struct ops_with_type* ops_struct;
        char *str;
        int number;
        


/* Line 214 of yacc.c  */
#line 222 "Collection.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 234 "Collection.tab.c"

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
# if YYENABLE_NLS
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
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  58
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   274

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  30
/* YYNRULES -- Number of rules.  */
#define YYNRULES  68
/* YYNRULES -- Number of states.  */
#define YYNSTATES  130

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   276

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    28,     2,
      30,    31,    26,    24,    35,    25,     2,    27,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    32,    22,
       2,    23,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    36,     2,    37,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    33,    29,    34,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    26,    30,    34,    38,    43,    46,    50,    54,
      58,    62,    66,    70,    72,    74,    76,    80,    81,    88,
      89,    96,    97,   106,   107,   111,   115,   119,   123,   127,
     131,   134,   138,   140,   145,   149,   154,   156,   157,   158,
     164,   166,   169,   171,   173,   177,   179,   181,   183,   185,
     187,   189,   193,   195,   199,   201,   204,   208,   211
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      39,     0,    -1,    39,    40,    -1,    40,    -1,    41,    -1,
      42,    -1,    43,    -1,    46,    -1,    53,    -1,    55,    -1,
      50,    -1,    16,    60,    22,    -1,    17,    60,    22,    -1,
      15,    60,    22,    -1,    14,    60,    22,    -1,    59,    23,
      44,    22,    -1,    44,    22,    -1,    44,    24,    45,    -1,
      44,    25,    45,    -1,    44,    26,    45,    -1,    44,    27,
      45,    -1,    44,    28,    45,    -1,    29,    44,    29,    -1,
      45,    -1,    61,    -1,    59,    -1,    30,    44,    31,    -1,
      -1,     6,    30,    52,    31,    47,    40,    -1,    -1,     9,
      30,    52,    31,    48,    40,    -1,    -1,     8,    30,    59,
      32,    59,    31,    49,    40,    -1,    -1,     7,    51,    40,
      -1,    44,    21,    44,    -1,    44,    20,    44,    -1,    44,
      10,    44,    -1,    44,    11,    44,    -1,    44,    12,    44,
      -1,    13,    52,    -1,    30,    52,    31,    -1,    44,    -1,
      18,    54,    59,    22,    -1,    19,    54,    22,    -1,    19,
      54,    44,    22,    -1,     3,    -1,    -1,    -1,    33,    56,
      58,    34,    57,    -1,    40,    -1,    58,    40,    -1,     4,
      -1,    59,    -1,    60,    35,    59,    -1,    62,    -1,    65,
      -1,    66,    -1,    67,    -1,     5,    -1,     5,    -1,    63,
      35,     5,    -1,     3,    -1,    64,    35,     3,    -1,     3,
      -1,    36,    37,    -1,    36,    63,    37,    -1,    33,    34,
      -1,    33,    64,    34,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,   104,   104,   105,   108,   109,   110,   111,   112,   113,
     114,   116,   117,   118,   119,   122,   125,   128,   129,   130,
     131,   132,   133,   134,   137,   138,   139,   142,   142,   143,
     143,   144,   144,   147,   147,   150,   151,   152,   153,   154,
     155,   156,   157,   160,   161,   162,   165,   168,   168,   168,
     171,   172,   175,   178,   179,   182,   183,   184,   185,   188,
     191,   192,   195,   196,   199,   202,   203,   206,   207
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "t_STRING", "t_ID", "t_INT", "t_IF_CMD",
  "t_ELSE_CMD", "t_FOR_CMD", "t_WHILE_CMD", "t_BIGGER_EQUAL",
  "t_LOWER_EQUAL", "t_EQUAL", "t_NOT", "t_COLLECTION_CMD", "t_SET_CMD",
  "t_INT_CMD", "t_STRING_CMD", "t_INPUT_CMD", "t_OUTPUT_CMD", "t_LOWER",
  "t_BIGGER", "';'", "'='", "'+'", "'-'", "'*'", "'/'", "'&'", "'|'",
  "'('", "')'", "':'", "'{'", "'}'", "','", "'['", "']'", "$accept",
  "prog", "statement", "declaration", "assignment", "operation_statement",
  "operation", "expression", "control", "$@1", "$@2", "$@3", "else_",
  "$@4", "condition", "io", "String_", "block", "$@5", "$@6",
  "statement_list", "identifier", "identifier_list", "literal",
  "number_literal", "INT_LIST", "STRING_LIST", "string_literal",
  "set_literal", "collection_literal", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,    59,    61,    43,    45,    42,    47,    38,   124,
      40,    41,    58,   123,   125,    44,    91,    93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    38,    39,    39,    40,    40,    40,    40,    40,    40,
      40,    41,    41,    41,    41,    42,    43,    44,    44,    44,
      44,    44,    44,    44,    45,    45,    45,    47,    46,    48,
      46,    49,    46,    51,    50,    52,    52,    52,    52,    52,
      52,    52,    52,    53,    53,    53,    54,    56,    57,    55,
      58,    58,    59,    60,    60,    61,    61,    61,    61,    62,
      63,    63,    64,    64,    65,    66,    66,    67,    67
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     3,     3,     4,     2,     3,     3,     3,
       3,     3,     3,     1,     1,     1,     3,     0,     6,     0,
       6,     0,     8,     0,     3,     3,     3,     3,     3,     3,
       2,     3,     1,     4,     3,     4,     1,     0,     0,     5,
       1,     2,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     3,     1,     3,     1,     2,     3,     2,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    64,    52,    59,     0,    33,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    47,     0,     0,     3,
       4,     5,     6,     0,    23,     7,    10,     8,     9,    25,
      24,    55,    56,    57,    58,     0,     0,     0,     0,    53,
       0,     0,     0,     0,    46,     0,     0,     0,     0,    25,
       0,    62,    67,     0,     0,    60,    65,     0,     1,     2,
      16,     0,     0,     0,     0,     0,     0,     0,     0,    42,
       0,    34,     0,     0,    14,     0,    13,    11,    12,     0,
      44,     0,    22,    26,    50,     0,    68,     0,     0,    66,
      17,    18,    19,    20,    21,     0,    40,     0,     0,     0,
       0,     0,     0,     0,    27,     0,    29,    54,    43,    45,
      48,    51,    63,    61,    15,    41,    37,    38,    39,    36,
      35,     0,     0,     0,    49,    28,    31,    30,     0,    32
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    18,    19,    20,    21,    22,    23,    24,    25,   121,
     123,   128,    26,    36,    70,    27,    45,    28,    53,   124,
      85,    49,    40,    30,    31,    57,    54,    32,    33,    34
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -31
static const yytype_int16 yypact[] =
{
     194,   -31,   -31,   -31,   -28,   -31,    -8,    -3,    38,    38,
      38,    38,    17,    17,    44,    44,    -2,     7,   126,   -31,
     -31,   -31,   -31,   124,   -31,   -31,   -31,   -31,   -31,    27,
     -31,   -31,   -31,   -31,   -31,    10,   194,    38,    10,   -31,
     -18,   -16,    -6,     6,   -31,    38,    30,    -2,   235,   -31,
      62,   -31,   -31,   194,   -10,   -31,   -31,   -30,   -31,   -31,
     -31,    64,    64,    64,    64,    64,    44,    10,    10,   230,
      26,   -31,    29,    33,   -31,    38,   -31,   -31,   -31,    36,
     -31,   158,   -31,   -31,   -31,   160,   -31,    68,    60,   -31,
     -31,   -31,   -31,   -31,   -31,   221,   -31,   208,    41,    44,
      44,    44,    44,    44,   -31,    38,   -31,   -31,   -31,   -31,
     -31,   -31,   -31,   -31,   -31,   -31,   241,   241,   241,   241,
     241,   194,    45,   194,   -31,   -31,   -31,   -31,   194,   -31
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -31,   -31,   -15,   -31,   -31,   -31,    16,   209,   -31,   -31,
     -31,   -31,   -31,   -31,   -12,   -31,    65,   -31,   -31,   -31,
     -31,     0,    92,   -31,   -31,   -31,   -31,   -31,   -31,   -31
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      29,    51,    35,    59,    74,    88,    76,    89,    39,    39,
      39,    39,    55,     1,     2,     3,    77,    75,    29,    75,
      44,    71,    37,    67,    86,    87,    73,    38,    78,    75,
      48,    50,    52,     1,     2,     3,    29,    72,    84,    14,
      68,    75,     2,    47,    56,    79,    17,     1,     2,     3,
      66,    69,    80,    29,    69,    96,    98,   104,   108,    14,
      15,   105,    81,    47,   106,   113,    17,     1,     2,     3,
     111,   112,   115,    14,    15,   107,   126,    47,    46,     0,
      17,     0,    95,    69,    97,    29,    61,    62,    63,    64,
      65,     0,     0,    83,    15,     0,     0,    47,     0,     0,
      17,    41,    42,    43,     0,   122,   125,     0,   127,     0,
       0,     0,     0,   129,     0,   116,   117,   118,   119,   120,
       0,    29,     0,    29,     0,     0,    58,     0,    29,     1,
       2,     3,     4,     5,     6,     7,     0,     0,     0,     0,
       8,     9,    10,    11,    12,    13,    60,     0,    61,    62,
      63,    64,    65,     0,     0,    14,    15,     0,     0,    16,
       0,     0,    17,     1,     2,     3,     4,     5,     6,     7,
       0,     0,     0,     0,     8,     9,    10,    11,    12,    13,
     109,     0,    61,    62,    63,    64,    65,     0,     0,    14,
      15,     0,     0,    16,   110,     0,    17,     1,     2,     3,
       4,     5,     6,     7,     0,     0,     0,     0,     8,     9,
      10,    11,    12,    13,     0,     0,     0,     0,    99,   100,
     101,     0,     0,    14,    15,     0,     0,    16,   102,   103,
      17,     0,    61,    62,    63,    64,    65,     0,     0,    83,
      99,   100,   101,   114,     0,    61,    62,    63,    64,    65,
     102,   103,     0,     0,    61,    62,    63,    64,    65,    61,
      62,    63,    64,    65,    82,    61,    62,    63,    64,    65,
      90,    91,    92,    93,    94
};

static const yytype_int16 yycheck[] =
{
       0,     3,    30,    18,    22,    35,    22,    37,     8,     9,
      10,    11,     5,     3,     4,     5,    22,    35,    18,    35,
       3,    36,    30,    13,    34,    35,    38,    30,    22,    35,
      14,    15,    34,     3,     4,     5,    36,    37,    53,    29,
      30,    35,     4,    33,    37,    45,    36,     3,     4,     5,
      23,    35,    22,    53,    38,    67,    68,    31,    22,    29,
      30,    32,    46,    33,    31,     5,    36,     3,     4,     5,
      85,     3,    31,    29,    30,    75,    31,    33,    13,    -1,
      36,    -1,    66,    67,    68,    85,    24,    25,    26,    27,
      28,    -1,    -1,    31,    30,    -1,    -1,    33,    -1,    -1,
      36,     9,    10,    11,    -1,   105,   121,    -1,   123,    -1,
      -1,    -1,    -1,   128,    -1,    99,   100,   101,   102,   103,
      -1,   121,    -1,   123,    -1,    -1,     0,    -1,   128,     3,
       4,     5,     6,     7,     8,     9,    -1,    -1,    -1,    -1,
      14,    15,    16,    17,    18,    19,    22,    -1,    24,    25,
      26,    27,    28,    -1,    -1,    29,    30,    -1,    -1,    33,
      -1,    -1,    36,     3,     4,     5,     6,     7,     8,     9,
      -1,    -1,    -1,    -1,    14,    15,    16,    17,    18,    19,
      22,    -1,    24,    25,    26,    27,    28,    -1,    -1,    29,
      30,    -1,    -1,    33,    34,    -1,    36,     3,     4,     5,
       6,     7,     8,     9,    -1,    -1,    -1,    -1,    14,    15,
      16,    17,    18,    19,    -1,    -1,    -1,    -1,    10,    11,
      12,    -1,    -1,    29,    30,    -1,    -1,    33,    20,    21,
      36,    -1,    24,    25,    26,    27,    28,    -1,    -1,    31,
      10,    11,    12,    22,    -1,    24,    25,    26,    27,    28,
      20,    21,    -1,    -1,    24,    25,    26,    27,    28,    24,
      25,    26,    27,    28,    29,    24,    25,    26,    27,    28,
      61,    62,    63,    64,    65
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    14,    15,
      16,    17,    18,    19,    29,    30,    33,    36,    39,    40,
      41,    42,    43,    44,    45,    46,    50,    53,    55,    59,
      61,    62,    65,    66,    67,    30,    51,    30,    30,    59,
      60,    60,    60,    60,     3,    54,    54,    33,    44,    59,
      44,     3,    34,    56,    64,     5,    37,    63,     0,    40,
      22,    24,    25,    26,    27,    28,    23,    13,    30,    44,
      52,    40,    59,    52,    22,    35,    22,    22,    22,    59,
      22,    44,    29,    31,    40,    58,    34,    35,    35,    37,
      45,    45,    45,    45,    45,    44,    52,    44,    52,    10,
      11,    12,    20,    21,    31,    32,    31,    59,    22,    22,
      34,    40,     3,     5,    22,    31,    44,    44,    44,    44,
      44,    47,    59,    48,    57,    40,    31,    40,    49,    40
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
# if YYLTYPE_IS_TRIVIAL
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
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
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
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
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


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

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
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

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
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
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

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
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

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
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
        case 2:

/* Line 1455 of yacc.c  */
#line 104 "Collection.y"
    {;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 105 "Collection.y"
    {;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 108 "Collection.y"
    {;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 109 "Collection.y"
    {;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 110 "Collection.y"
    {;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 111 "Collection.y"
    {;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 112 "Collection.y"
    {;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 113 "Collection.y"
    {;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 114 "Collection.y"
    {;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 116 "Collection.y"
    {declaration((yyvsp[(2) - (3)].str), Int);;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 117 "Collection.y"
    {declaration((yyvsp[(2) - (3)].str), String);;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 118 "Collection.y"
    {declaration((yyvsp[(2) - (3)].str), Set);;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 119 "Collection.y"
    {declaration((yyvsp[(2) - (3)].str), Collection);;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 122 "Collection.y"
    {assignment_op((yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].ops_struct));;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 125 "Collection.y"
    {printf("%s;\n", (yyvsp[(1) - (2)].ops_struct)->value);;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 128 "Collection.y"
    {(yyval.ops_struct) = operation_with_command((yyvsp[(1) - (3)].ops_struct),'+',(yyvsp[(3) - (3)].ops_struct));;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 129 "Collection.y"
    {(yyval.ops_struct) = operation_with_command((yyvsp[(1) - (3)].ops_struct),'-',(yyvsp[(3) - (3)].ops_struct));;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 130 "Collection.y"
    {(yyval.ops_struct) = operation_with_command((yyvsp[(1) - (3)].ops_struct),'*',(yyvsp[(3) - (3)].ops_struct));;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 131 "Collection.y"
    {(yyval.ops_struct) = operation_with_command((yyvsp[(1) - (3)].ops_struct),'/',(yyvsp[(3) - (3)].ops_struct));;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 132 "Collection.y"
    {(yyval.ops_struct) = operation_with_command((yyvsp[(1) - (3)].ops_struct),'&',(yyvsp[(3) - (3)].ops_struct));;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 133 "Collection.y"
    {(yyval.ops_struct) = size_set_or_collection((yyvsp[(2) - (3)].ops_struct));;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 134 "Collection.y"
    {(yyval.ops_struct) = (yyvsp[(1) - (1)].ops_struct);;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 137 "Collection.y"
    {(yyval.ops_struct) = create_ops_with_type_literal((yyvsp[(1) - (1)].literal_struct));;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 138 "Collection.y"
    {(yyval.ops_struct) = create_ops_with_type_identifier((yyvsp[(1) - (1)].str));;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 139 "Collection.y"
    {(yyval.ops_struct) = add_bracets_to_op((yyvsp[(2) - (3)].ops_struct));;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 142 "Collection.y"
    {printf("if(%s)\n",(yyvsp[(3) - (4)].ops_struct)->value);}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 142 "Collection.y"
    {;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 143 "Collection.y"
    {printf("while(%s)\n",(yyvsp[(3) - (4)].ops_struct)->value);;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 143 "Collection.y"
    {;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 144 "Collection.y"
    {for_loop((yyvsp[(3) - (6)].str),(yyvsp[(5) - (6)].str));}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 144 "Collection.y"
    {;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 147 "Collection.y"
    {printf("else\n");}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 147 "Collection.y"
    {;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 150 "Collection.y"
    {(yyval.ops_struct) = condition_op((yyvsp[(1) - (3)].ops_struct), ">", (yyvsp[(3) - (3)].ops_struct));;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 151 "Collection.y"
    {(yyval.ops_struct) = condition_op((yyvsp[(1) - (3)].ops_struct), "<", (yyvsp[(3) - (3)].ops_struct));;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 152 "Collection.y"
    {(yyval.ops_struct) = condition_op((yyvsp[(1) - (3)].ops_struct), ">=", (yyvsp[(3) - (3)].ops_struct));;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 153 "Collection.y"
    {(yyval.ops_struct) = condition_op((yyvsp[(1) - (3)].ops_struct), "<=", (yyvsp[(3) - (3)].ops_struct));;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 154 "Collection.y"
    {(yyval.ops_struct) = condition_op((yyvsp[(1) - (3)].ops_struct), "==", (yyvsp[(3) - (3)].ops_struct));;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 155 "Collection.y"
    {(yyval.ops_struct) = not_condition_op((yyvsp[(2) - (2)].ops_struct));;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 156 "Collection.y"
    {(yyval.ops_struct) = add_bracets_to_op((yyvsp[(2) - (3)].ops_struct));;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 157 "Collection.y"
    {if((yyvsp[(1) - (1)].ops_struct)->type == Set || (yyvsp[(1) - (1)].ops_struct)->type == Collection) (yyval.ops_struct) = size_set_or_collection((yyvsp[(1) - (1)].ops_struct)); else (yyval.ops_struct) = (yyvsp[(1) - (1)].ops_struct);;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 160 "Collection.y"
    {printf("input_from_user(make_literal(\"%s\"),%s);\n",(yyvsp[(2) - (4)].str),(yyvsp[(3) - (4)].str));;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 161 "Collection.y"
    {printf("printSetWithMessage(\"%s\");\n",(yyvsp[(2) - (3)].str));;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 162 "Collection.y"
    {GenerateOut((yyvsp[(2) - (4)].str), (yyvsp[(3) - (4)].ops_struct)->value);;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 165 "Collection.y"
    {(yyval.str) = copy_string_without_quotes(yytext);;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 168 "Collection.y"
    {printf("{\n");}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 168 "Collection.y"
    {printf("}\n");}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 168 "Collection.y"
    {;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 171 "Collection.y"
    {;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 172 "Collection.y"
    {;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 175 "Collection.y"
    {(yyval.str) = CopyStr(yytext);;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 178 "Collection.y"
    {(yyval.str) = (yyvsp[(1) - (1)].str);}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 179 "Collection.y"
    {(yyval.str) = AddToList((yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].str)); free((yyvsp[(3) - (3)].str));;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 182 "Collection.y"
    {(yyval.literal_struct) = malloc(sizeof(struct literal_with_type)); (yyval.literal_struct)->type = Int; (yyval.literal_struct)->value = (yyvsp[(1) - (1)].str); ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 183 "Collection.y"
    {(yyval.literal_struct) = malloc(sizeof(struct literal_with_type)); (yyval.literal_struct)->type = String; (yyval.literal_struct)->value = (yyvsp[(1) - (1)].str); ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 184 "Collection.y"
    {(yyval.literal_struct) = malloc(sizeof(struct literal_with_type)); (yyval.literal_struct)->type = Set; (yyval.literal_struct)->value = (yyvsp[(1) - (1)].str);  ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 185 "Collection.y"
    {(yyval.literal_struct) = malloc(sizeof(struct literal_with_type)); (yyval.literal_struct)->type = Collection; (yyval.literal_struct)->value = (yyvsp[(1) - (1)].str);;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 188 "Collection.y"
    {(yyval.str) = CopyINT(yytext);;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 191 "Collection.y"
    {(yyval.str) = CopyINT(yytext);;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 192 "Collection.y"
    {(yyval.str) = AddToList((yyvsp[(1) - (3)].str), yytext);;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 195 "Collection.y"
    {(yyval.str) = copy_string_without_quotes(yytext);;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 196 "Collection.y"
    {(yyval.str) = AddToList((yyvsp[(1) - (3)].str), copy_string_without_quotes(yytext));;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 199 "Collection.y"
    {(yyval.str) = copy_string_without_quotes(yytext);;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 202 "Collection.y"
    {(yyval.str) = CopyINT("\0");;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 203 "Collection.y"
    {(yyval.str) = (yyvsp[(2) - (3)].str);;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 206 "Collection.y"
    {(yyval.str) = CopyINT("\0");;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 207 "Collection.y"
    {(yyval.str) = (yyvsp[(2) - (3)].str);;}
    break;



/* Line 1455 of yacc.c  */
#line 2034 "Collection.tab.c"
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
      /* If just tried and failed to reuse lookahead token after an
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

  /* Else will try to reuse lookahead token after shifting the error
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

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
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



/* Line 1675 of yacc.c  */
#line 213 "Collection.y"

extern int yylineno;

void yyerror(char *s) {
    fprintf(stderr, "Error: %s at line %d\n", s, yylineno);
}
int main(void) {


    outputFile = freopen("test.cpp", "w", stdout);
    if (outputFile == NULL) {
        fprintf(stderr, "Error opening output file.\n");
        return 1;
    }

    inputFile = freopen("INPUT.txt", "r", stdin);
    if (inputFile == NULL) {
        fprintf(stderr, "Error opening input file.\n");
        return 1;
    }

    fprintf(stdout, "#include <stdio.h>\n");
    fprintf(stdout, "#include <stdlib.h>\n");
    fprintf(stdout, "#include <string.h>\n");
    fprintf(stdout, "#include <iostream>\n");
    fprintf(stdout, "#include <string>\n");
    fprintf(stdout, "#include <set>\n\n");
    fprintf(stdout, "#include <sstream>\n\n");
    fprintf(stdout, "#include <algorithm>\n\n");
    fprintf(stdout, "#include <initializer_list>\n\n");
    
    fprintf(stdout, "using namespace std;\n\n");

    fprintf(stdout, "template<typename T>\n");
    fprintf(stdout, "set<T> make_literal(initializer_list<T> list) {\n");
    fprintf(stdout, "    return set<T>(list);\n");
    fprintf(stdout, "}\n");

    fprintf(stdout, "//COLLECTION operators\n");
    fprintf(stdout, "set<string> operator-(const set<string>& set1, const set<string>& set2) {\n");
    fprintf(stdout, "    set<string> result = set1;\n");
    fprintf(stdout, "    for (const string& elem : set2) {\n");
    fprintf(stdout, "        result.erase(elem);\n");
    fprintf(stdout, "    }\n");
    fprintf(stdout, "    return result;\n");
    fprintf(stdout, "}\n");
    
    fprintf(stdout, "set<string> operator+(const set<string>& set1, const set<string>& set2) {\n");
    fprintf(stdout, "    set<string> result = set1;\n");
    fprintf(stdout, "    result.insert(set2.begin(), set2.end());\n");
    fprintf(stdout, "    return result;\n");
    fprintf(stdout, "}\n");

    fprintf(stdout, "set<string> operator+(const set<string>& set1, const string& str) {\n");
    fprintf(stdout, "    set<string> result = set1;\n");
    fprintf(stdout, "    result.insert(str);\n");
    fprintf(stdout, "    return result;\n");
    fprintf(stdout, "}\n");

    fprintf(stdout, "set<string> operator*(const set<string>& set1, const set<string>& set2) {\n");
    fprintf(stdout, "    set<string> result;\n");
    fprintf(stdout, "    for (const string& elem : set1) {\n");
    fprintf(stdout, "        if (set2.find(elem) != set2.end()) {\n");
    fprintf(stdout, "            result.insert(elem);\n");
    fprintf(stdout, "        }\n");
    fprintf(stdout, "    }\n");
    fprintf(stdout, "    return result;\n");
    fprintf(stdout, "}\n");

    fprintf(stdout, "void printSetWithMessage(const set<string>& mySet, const string& message) {\n");
    fprintf(stdout, "    cout << message << \" {\";\n");
    fprintf(stdout, "    auto it = mySet.begin();\n");
    fprintf(stdout, "    if (it != mySet.end()) {\n");
    fprintf(stdout, "        cout << \"\\\"\" << *it << \"\\\"\";\n");
    fprintf(stdout, "        ++it;\n");
    fprintf(stdout, "    }\n");
    fprintf(stdout, "    while (it != mySet.end()) {\n");
    fprintf(stdout, "        cout << \", \\\"\" << *it << \"\\\"\";\n");
    fprintf(stdout, "        ++it;\n");
    fprintf(stdout, "    }\n");
    fprintf(stdout, "    cout << \"}\" << endl;\n");
    fprintf(stdout, "}\n");

    fprintf(stdout, "//SET operators\n");
    fprintf(stdout, "set<int> operator-(const set<int>& set1, const set<int>& set2) {\n");
    fprintf(stdout, "    set<int> result = set1;\n");
    fprintf(stdout, "    for (const int& elem : set2) {\n");
    fprintf(stdout, "        result.erase(elem);\n");
    fprintf(stdout, "    }\n");
    fprintf(stdout, "    return result;\n");
    fprintf(stdout, "}\n");
    
    fprintf(stdout, "set<int> operator+(const set<int>& set1, const set<int>& set2) {\n");
    fprintf(stdout, "    set<int> result = set1;\n");
    fprintf(stdout, "    result.insert(set2.begin(), set2.end());\n");
    fprintf(stdout, "    return result;\n");
    fprintf(stdout, "}\n");

    fprintf(stdout, "set<int> operator+(const set<int>& set1, const int& str) {\n");
    fprintf(stdout, "    set<int> result = set1;\n");
    fprintf(stdout, "    result.insert(str);\n");
    fprintf(stdout, "    return result;\n");
    fprintf(stdout, "}\n");

    fprintf(stdout, "set<int> operator*(const set<int>& set1, const set<int>& set2) {\n");
    fprintf(stdout, "    set<int> result;\n");
    fprintf(stdout, "    for (const int& elem : set1) {\n");
    fprintf(stdout, "        if (set2.find(elem) != set2.end()) {\n");
    fprintf(stdout, "            result.insert(elem);\n");
    fprintf(stdout, "        }\n");
    fprintf(stdout, "    }\n");
    fprintf(stdout, "    return result;\n");
    fprintf(stdout, "}\n");

    fprintf(stdout, "void printSetWithMessage(const set<int>& mySet, const string& message) {\n");
    fprintf(stdout, "    cout << message << \" [\";\n");
    fprintf(stdout, "    auto it = mySet.begin();\n");
    fprintf(stdout, "    if (it != mySet.end()) {\n");
    fprintf(stdout, "        cout << *it ;\n");
    fprintf(stdout, "        ++it;\n");
    fprintf(stdout, "    }\n");
    fprintf(stdout, "    while (it != mySet.end()) {\n");
    fprintf(stdout, "        cout << \",\" << *it ;\n");
    fprintf(stdout, "        ++it;\n");
    fprintf(stdout, "    }\n");
    fprintf(stdout, "    cout << \"]\" << endl;\n");
    fprintf(stdout, "}\n");

    fprintf(stdout, "//INT operators\n");
    fprintf(stdout, "int make_literal(int list) {\n");
    fprintf(stdout, "    return list;\n");
    fprintf(stdout, "}\n");

    fprintf(stdout, "void printSetWithMessage(const int& myINT, const string& message) {\n");
    fprintf(stdout, "    cout << message << \" \" << myINT << endl;\n");
    fprintf(stdout, "}\n");

    fprintf(stdout, "//STRING operators\n");
    fprintf(stdout, "string make_literal(string list) {\n");
    fprintf(stdout, "    return list;\n");
    fprintf(stdout, "}\n");

    fprintf(stdout, "void printSetWithMessage(const string& mySTR, const string& message) {\n");
    fprintf(stdout, "    cout << message << \" \\\"\" << mySTR << \"\\\"\" << endl;\n");
    fprintf(stdout, "}\n");

    
    fprintf(stdout, "//input from the user for each identifier type\n");
    fprintf(stdout, "void input_from_user(const string &massage, int &identifier) {\n");
    fprintf(stdout, "    cout << massage;\n");
    fprintf(stdout, "    cin >> identifier;\n");
    fprintf(stdout, "}\n");

    fprintf(stdout, "void input_from_user(const string &massage, string &identifier) {\n");
    fprintf(stdout, "    cout << massage;\n");
    fprintf(stdout, "    cin >> identifier;\n");
    fprintf(stdout, "}\n");

    printf("void input_from_user(const string &message, set<string> &words) {\n");
    printf("    cout << message;\n\n");

    printf("    // Skip any leftover newline characters from previous input\n");
    printf("    if (cin.peek() == '\\n') {\n");
    printf("        cin.ignore();\n");
    printf("    }\n\n");

    printf("    string temp;\n");
    printf("    getline(cin, temp);\n");
    printf("    words.clear();\n\n");

    printf("    if (!temp.empty() && (temp.front() == '{' && temp.back() == '}')) {\n");
    printf("        temp = temp.substr(1, temp.size() - 2);\n");
    printf("    }\n\n");

    printf("    string temp_word;\n");
    printf("    bool in_quotes = false;\n\n");

    printf("    for (size_t i = 0; i < temp.size(); ++i) {\n");
    printf("        if (temp[i] == '\"') {\n");
    printf("            in_quotes = !in_quotes;\n");
    printf("        } else if (temp[i] == ',' && !in_quotes) {\n");
    printf("            temp_word.erase(temp_word.find_last_not_of(\" \\t\") + 1);\n");
    printf("            if (!temp_word.empty()) {\n");
    printf("                if (temp_word.front() != '\"' && temp_word.back() != '\"') {\n");
    printf("                    words.insert(temp_word);\n");
    printf("                } else {\n");
    printf("                    temp_word.erase(0, temp_word.find_first_not_of('\"'));\n");
    printf("                    temp_word.erase(temp_word.find_last_not_of('\"') + 1);\n");
    printf("                    if (!temp_word.empty()) {\n");
    printf("                        words.insert(temp_word);\n");
    printf("                    }\n");
    printf("                }\n");
    printf("                temp_word.clear();\n");
    printf("            }\n");
    printf("        } else if (temp[i] == ' ' && !in_quotes) {\n");
    printf("            continue;\n");
    printf("        } else {\n");
    printf("            temp_word += temp[i];\n");
    printf("        }\n");
    printf("    }\n");
    printf("    temp_word.erase(temp_word.find_last_not_of(\" \\t\") + 1);\n");
    printf("    if (!temp_word.empty()) {\n");
    printf("        if (temp_word.front() != '\"' && temp_word.back() != '\"') {\n");
    printf("            words.insert(temp_word);\n");
    printf("        } else {\n");
    printf("            temp_word.erase(0, temp_word.find_first_not_of('\"'));\n");
    printf("            temp_word.erase(temp_word.find_last_not_of('\"') + 1);\n");
    printf("            if (!temp_word.empty()) {\n");
    printf("                words.insert(temp_word);\n");
    printf("            }\n");
    printf("        }\n");
    printf("    }\n");
    printf("}\n");

    fprintf(stdout, "void input_from_user(const string &message, set<int> &numbers) {\n");
    fprintf(stdout, "    cout << message;\n");
    fprintf(stdout, "\n");
    fprintf(stdout, "    cin.clear();\n");
    fprintf(stdout, "\n");
    fprintf(stdout, "    string temp;\n");
    fprintf(stdout, "\n");
    fprintf(stdout, "    getline(cin, temp);\n");
    fprintf(stdout, "    numbers.clear();\n");
    fprintf(stdout, "\n");
    fprintf(stdout, "    if (!temp.empty() && temp.front() == '[' && temp.back() == ']') {\n");
    fprintf(stdout, "        temp = temp.substr(1, temp.size() - 2);\n");
    fprintf(stdout, "    }\n");
    fprintf(stdout, "\n");
    fprintf(stdout, "    string temp_number;\n");
    fprintf(stdout, "    for (size_t i = 0; i < temp.size(); ++i) {\n");
    fprintf(stdout, "        if (isdigit(temp[i]) || (temp[i] == '-' && i + 1 < temp.size() && isdigit(temp[i + 1]))) {\n");
    fprintf(stdout, "            temp_number += temp[i];\n");
    fprintf(stdout, "        } else if (temp[i] == ',' || temp[i] == ' ') {\n");
    fprintf(stdout, "            if (!temp_number.empty()) {\n");
    fprintf(stdout, "                numbers.insert(stoi(temp_number));\n");
    fprintf(stdout, "                temp_number.clear();\n");
    fprintf(stdout, "            }\n");
    fprintf(stdout, "        }\n");
    fprintf(stdout, "    }\n");
    fprintf(stdout, "    if (!temp_number.empty()) {\n");
    fprintf(stdout, "        numbers.insert(stoi(temp_number));\n");
    fprintf(stdout, "    }\n");
    fprintf(stdout, "}\n");


    fprintf(stdout, "void printSetWithMessage(const string& message) {\n");
    fprintf(stdout, "    cout << message << endl;\n");
    fprintf(stdout, "}\n");
    
    fprintf(stdout, "int main()\n");
    fprintf(stdout, "{\n");
    yyparse();

    fprintf(stdout, "}\n");
    if (fclose(outputFile) != 0) {
        fprintf(stderr, "Error closing output file.\n");
    }
    if (fclose(inputFile) != 0) {
        fprintf(stderr, "Error closing input file.\n");
    }

}

