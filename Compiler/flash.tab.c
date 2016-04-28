
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
#line 1 "flash.y"
/*************************************************************************
			Compiler for the Flash language
***************************************************************************/
/*=========================================================================
	C Libraries, Symbol Table, Code Generator & other C code
=========================================================================*/
#include<memory.h>

#include <stdio.h>
/* For I/O																*/
#include <stdlib.h>
/* For malloc here and in symbol table									*/
#include <string.h>
/* For strcmp in symbol table											*/
#include "ST.h"
/* Symbol Table															*/
#include "SM.h"
/* Stack Machine														*/
#include "CG.h"
/* Code Generator														*/
#include "queue.h"
/* For formal parameters and arguments type check						*/
#define YYDEBUG 1
/* For Debugging														*/
int errors;
extern int yylineno;
/* Error Count*/
/*-------------------------------------------------------------------------
				The following supports a block structure
-------------------------------------------------------------------------*/
int fun_offset = 0;
int arg_offset = 0; 
int block_offset = 0;
int block_in()
{
  block_offset = block_offset + 1;
}
int reset_block()
{
  block_offset = 0;
}
/*-------------------------------------------------------------------------
				The following support backpatching
-------------------------------------------------------------------------*/
struct lbs
/* Labels for data, if and while*/
{
	int for_goto;
	int for_jmp_false;
};
struct lbs * newlblrec() /*      Allocate space for the labels			*/
{
	return (struct lbs *) malloc(sizeof(struct lbs));
}
/*-------------------------------------------------------------------------
				Install identifier & check if previously defined.
-------------------------------------------------------------------------*/
install ( char *sym_name ,int type, int block)
{
	symrec *s;
	s = getsym (sym_name);
	if (s == 0) {
		s = putsym (sym_name,type, block);
	}
	else if (s->block_offset != block){
		s = putsym (sym_name,type, block);
	}
	else { errors++;
		yyerror( strcat(sym_name, " is already defined") );
	}
}
/*-------------------------------------------------------------------------
				If identifier is defined, generate code
-------------------------------------------------------------------------*/
context_check( enum code_ops operation, char *sym_name ,int type)
{   symrec *identifier;
	identifier = getsym( sym_name );
	if ( identifier == 0 ) { 
		errors++;
		yyerror( strcat(sym_name," is an undeclared identifier") );
		}
	else if (type != -1 && identifier->type != type) {
		yyerror( strcat(sym_name," type error!") );
		}
	else gen_code( operation, identifier->offset );
}

context_check_fun( enum code_ops operation, char *sym_name ,int type)		
{   symrec *identifier;		
	identifier = getsym( sym_name );
	fun_offset = identifier->block_offset;		
	if ( identifier == 0 ) { 		
		errors++;		
		yyerror( strcat(sym_name," is an undeclared identifier") );	
		}		
	else if (type != -1 && identifier->type != type) {		
		yyerror( strcat(sym_name," type error!") );	
		}		
	else gen_fun( operation, identifier->name );		
}

argument_check(char* sym_name, int arg)
{
	
	symrec *identifier;		
	identifier = getsym( sym_name );
	int n = identifier->type; 
	char * checker = as[fun_offset-1].q.element[arg_offset-1];
	if ( identifier == 0 ) { 
		errors++;
		yyerror( strcat(sym_name," is an undeclared identifier") );
		}
	else {
			if ( !strcmp(checker,"PARA_INT")  &&	identifier->type != 1 )
				yyerror( strcat(sym_name," parameter type mismatch!") );
			else if (!strcmp(checker,"PARA_BOOL")  &&	identifier->type != 0 )
				yyerror( strcat(sym_name," parameter type mismatch!") );
			else if (!strcmp(checker,"PARA_STR")  &&	identifier->type != 2 )
				yyerror( strcat(sym_name," parameter type mismatch!") );
			}
	gen_code( ARG, identifier->offset );
}	

/*=========================================================================
							SEMANTIC RECORDS
=========================================================================*/


/* Line 189 of yacc.c  */
#line 202 "flash.tab.c"

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
     STRING = 258,
     BOOLEAN = 259,
     NUMBER = 260,
     IDENTIFIER = 261,
     IF = 262,
     WHILE = 263,
     SKIP = 264,
     THEN = 265,
     ELSE = 266,
     FI = 267,
     DO = 268,
     END = 269,
     INTEGER = 270,
     READ = 271,
     WRITE = 272,
     LET = 273,
     IN = 274,
     BOOLE = 275,
     STR = 276,
     STACK = 277,
     ASSGNOP = 278,
     LEQ = 279,
     GEQ = 280,
     ONTO = 281,
     OUTFROM = 282,
     FUN = 283,
     END_FUN = 284,
     RETURN = 285,
     CALL = 286
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union 
/* Line 214 of yacc.c  */
#line 128 "flash.y"
semrec
{

/* Line 214 of yacc.c  */
#line 129 "flash.y"

int	intval;								/* Integer value */
char *id;								/* Identifiers	*/
struct lbs *lbls;						/* For backpatching	*/
char *boolval;	
char *strval;						



/* Line 214 of yacc.c  */
#line 282 "flash.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 294 "flash.tab.c"

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
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   235

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  47
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  32
/* YYNRULES -- Number of rules.  */
#define YYNRULES  81
/* YYNRULES -- Number of states.  */
#define YYNSTATES  158

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   286

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,    43,     2,     2,     2,     2,
      38,    39,    34,    33,    40,    32,    46,    35,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    37,
      41,    45,    42,     2,    44,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    36,     2,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,    12,    13,    16,    18,    23,    28,
      33,    37,    38,    41,    42,    52,    53,    56,    58,    62,
      66,    70,    71,    74,    75,    79,    80,    84,    85,    89,
      90,    94,    95,    99,   101,   107,   112,   115,   116,   123,
     124,   133,   136,   140,   144,   147,   151,   155,   159,   163,
     167,   168,   169,   170,   181,   182,   183,   191,   192,   193,
     194,   205,   206,   207,   215,   217,   219,   223,   227,   231,
     235,   239,   243,   247,   251,   255,   259,   263,   265,   267,
     269,   271
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      48,     0,    -1,    -1,    18,    50,    52,    19,    49,    62,
      14,    -1,    -1,    50,    51,    -1,     9,    -1,    15,    59,
       6,    37,    -1,    20,    60,     6,    37,    -1,    21,    61,
       6,    37,    -1,    22,     6,    37,    -1,    -1,    52,    53,
      -1,    -1,    28,     6,    54,    38,    55,    39,    50,    62,
      29,    -1,    -1,    55,    56,    -1,     9,    -1,    15,     6,
      37,    -1,    20,     6,    37,    -1,    21,     6,    37,    -1,
      -1,    58,     6,    -1,    -1,    58,     6,    40,    -1,    -1,
      59,     6,    40,    -1,    -1,    60,     6,    40,    -1,    -1,
      61,     6,    40,    -1,    -1,    62,    63,    37,    -1,     9,
      -1,     6,    26,    41,    76,    42,    -1,     6,    23,     6,
      27,    -1,    30,     6,    -1,    -1,    31,     6,    64,    38,
      57,    39,    -1,    -1,     6,    23,    31,     6,    65,    38,
      57,    39,    -1,    16,     6,    -1,    16,    43,     6,    -1,
      16,    44,     6,    -1,    17,    76,    -1,    17,    43,    77,
      -1,    17,    44,    78,    -1,     6,    23,    76,    -1,     6,
      23,    77,    -1,     6,    23,    78,    -1,    -1,    -1,    -1,
       7,    76,    66,    10,    62,    67,    11,    68,    62,    12,
      -1,    -1,    -1,     8,    69,    76,    70,    13,    62,    14,
      -1,    -1,    -1,    -1,     7,    77,    71,    10,    62,    72,
      11,    73,    62,    12,    -1,    -1,    -1,     8,    74,    77,
      75,    13,    62,    14,    -1,     5,    -1,     6,    -1,    76,
      41,    76,    -1,    76,    45,    76,    -1,    76,    42,    76,
      -1,    76,    25,    76,    -1,    76,    24,    76,    -1,    76,
      33,    76,    -1,    76,    32,    76,    -1,    76,    34,    76,
      -1,    76,    35,    76,    -1,    76,    36,    76,    -1,    38,
      76,    39,    -1,     4,    -1,     6,    -1,     3,    -1,     6,
      -1,    78,    46,    78,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   162,   162,   159,   167,   168,   170,   171,   176,   181,
     186,   192,   193,   196,   195,   210,   211,   213,   214,   221,
     228,   236,   237,   243,   244,   251,   252,   258,   259,   265,
     266,   272,   273,   275,   276,   280,   285,   290,   289,   300,
     299,   310,   314,   318,   322,   326,   330,   334,   338,   342,
     350,   355,   359,   349,   368,   373,   367,   388,   393,   397,
     387,   406,   411,   405,   422,   423,   424,   425,   426,   427,
     428,   429,   430,   431,   432,   433,   434,   436,   437,   439,
     440,   441
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "STRING", "BOOLEAN", "NUMBER",
  "IDENTIFIER", "IF", "WHILE", "SKIP", "THEN", "ELSE", "FI", "DO", "END",
  "INTEGER", "READ", "WRITE", "LET", "IN", "BOOLE", "STR", "STACK",
  "ASSGNOP", "LEQ", "GEQ", "ONTO", "OUTFROM", "FUN", "END_FUN", "RETURN",
  "CALL", "'-'", "'+'", "'*'", "'/'", "'^'", "';'", "'('", "')'", "','",
  "'<'", "'>'", "'#'", "'@'", "'='", "'.'", "$accept", "program", "$@1",
  "declaration", "declarations", "functions", "fun", "$@2", "parameter",
  "parameters", "arguments", "argument", "id_seqi", "id_seqb", "id_seqs",
  "commands", "command", "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9",
  "$@10", "$@11", "$@12", "$@13", "$@14", "exp_int", "exp_bol", "exp_str", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,    45,    43,    42,    47,    94,    59,    40,    41,
      44,    60,    62,    35,    64,    61,    46
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    47,    49,    48,    50,    50,    51,    51,    51,    51,
      51,    52,    52,    54,    53,    55,    55,    56,    56,    56,
      56,    57,    57,    58,    58,    59,    59,    60,    60,    61,
      61,    62,    62,    63,    63,    63,    63,    64,    63,    65,
      63,    63,    63,    63,    63,    63,    63,    63,    63,    63,
      66,    67,    68,    63,    69,    70,    63,    71,    72,    73,
      63,    74,    75,    63,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    77,    77,    78,
      78,    78
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     7,     0,     2,     1,     4,     4,     4,
       3,     0,     2,     0,     9,     0,     2,     1,     3,     3,
       3,     0,     2,     0,     3,     0,     3,     0,     3,     0,
       3,     0,     3,     1,     5,     4,     2,     0,     6,     0,
       8,     2,     3,     3,     2,     3,     3,     3,     3,     3,
       0,     0,     0,    10,     0,     0,     7,     0,     0,     0,
      10,     0,     0,     7,     1,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     1,     1,     1,
       1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     4,     0,    11,     1,     6,    25,    27,    29,     0,
       5,     0,     0,     0,     0,     0,     2,     0,    12,     0,
       0,     0,    10,    31,    13,     7,    26,     8,    28,     9,
      30,     0,     0,     0,     0,    54,    33,     3,     0,     0,
       0,     0,     0,    15,     0,     0,    77,    64,    65,     0,
      50,    57,     0,     0,    41,     0,     0,    65,     0,     0,
      44,    36,    37,    32,     0,    79,    65,     0,    47,    48,
      49,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    55,    78,    62,    42,    43,
      45,    80,    46,     0,    17,     0,     0,     0,     4,    16,
      35,    39,     0,     0,    76,    70,    69,    72,    71,    73,
      74,    75,    66,    68,    67,    31,    31,     0,     0,    21,
       0,     0,     0,    31,     0,    81,    34,    51,    58,    31,
      31,     0,     0,    18,    19,    20,     0,    21,     0,     0,
       0,     0,    38,    22,    14,     0,    52,    59,    56,    63,
      24,    40,    31,    31,     0,     0,    53,    60
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,    23,     3,    10,    11,    18,    32,    64,    99,
     131,   132,    12,    13,    14,    31,    42,    93,   124,    83,
     138,   152,    52,   117,    84,   139,   153,    53,   118,   113,
      51,    70
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -103
static const yytype_int16 yypact[] =
{
     -12,  -103,     7,   208,  -103,  -103,  -103,  -103,  -103,     5,
    -103,    45,     6,    17,    28,    -1,  -103,    32,  -103,    22,
      39,    62,  -103,  -103,  -103,  -103,  -103,  -103,  -103,  -103,
    -103,    61,    25,    77,    -3,    70,  -103,  -103,    13,    11,
      75,    76,    46,  -103,    27,    53,  -103,  -103,  -103,    47,
     163,  -103,    47,    18,  -103,    89,    95,  -103,    18,   117,
     163,  -103,  -103,  -103,    51,  -103,    34,   102,   163,  -103,
      67,    47,   141,    47,    47,    47,    47,    47,    47,    47,
      47,    47,    47,   111,   112,   163,  -103,  -103,  -103,  -103,
    -103,  -103,    67,    87,  -103,   124,   125,   130,  -103,  -103,
    -103,  -103,   117,   177,  -103,   163,   163,   190,   190,   -16,
     -16,   -16,   163,   163,   163,  -103,  -103,   135,   136,   131,
     114,   115,   116,   208,   101,    67,    47,   154,   154,  -103,
    -103,   119,   153,  -103,  -103,  -103,    80,   131,   156,   161,
      98,   110,  -103,   139,  -103,   142,  -103,  -103,  -103,  -103,
    -103,  -103,  -103,  -103,   126,   138,  -103,  -103
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -103,  -103,  -103,    66,  -103,  -103,  -103,  -103,  -103,  -103,
      41,  -103,  -103,  -103,  -103,  -102,  -103,  -103,  -103,  -103,
    -103,  -103,  -103,  -103,  -103,  -103,  -103,  -103,  -103,   -34,
      40,   -55
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -81
static const yytype_int16 yytable[] =
{
      50,    46,    47,    48,    92,    60,     1,     4,    73,    74,
      68,    15,    19,   127,   128,    72,    47,    57,    85,    54,
      79,   136,    46,    20,    86,    80,    81,   140,   141,    82,
      65,    46,    47,    66,    21,    49,    22,   103,    24,   105,
     106,   107,   108,   109,   110,   111,   112,   125,   114,    49,
     154,   155,    47,    57,    58,    59,    55,    56,    67,    25,
      94,   100,    26,    43,    16,    49,    95,    33,    34,    35,
      36,    96,    97,    17,   -61,    37,    27,    38,    39,    28,
     -80,    61,    62,    63,    69,    49,    33,    34,    35,    36,
      98,    40,    41,    87,    71,    88,    38,    39,    90,    29,
      44,    89,    30,    45,    33,    34,    35,    36,   101,   144,
      40,    41,   148,   102,    38,    39,    33,    34,    35,    36,
      65,   115,   116,    91,   149,   119,    38,    39,    40,    41,
     120,   121,    33,    34,    35,    36,   122,   -23,   156,   137,
      40,    41,    38,    39,    33,    34,    35,    36,   129,   130,
     157,   133,   134,   135,    38,    39,    40,    41,   142,   143,
      33,    34,    35,    36,   123,    73,    74,   146,    40,    41,
      38,    39,   147,    75,    76,    77,    78,    79,   145,   150,
     104,   151,    80,    81,    40,    41,    82,    73,    74,     0,
       0,     0,     0,     0,     0,    75,    76,    77,    78,    79,
       0,    73,    74,     0,    80,    81,     0,     0,    82,    75,
      76,    77,    78,    79,    73,    74,     0,     5,    80,   126,
       0,     0,    82,     6,    77,    78,    79,     0,     7,     8,
       9,    80,    81,     0,     0,    82
};

static const yytype_int16 yycheck[] =
{
      34,     4,     5,     6,    59,    39,    18,     0,    24,    25,
      44,     6,     6,   115,   116,    49,     5,     6,    52,     6,
      36,   123,     4,     6,     6,    41,    42,   129,   130,    45,
       3,     4,     5,     6,     6,    38,    37,    71,     6,    73,
      74,    75,    76,    77,    78,    79,    80,   102,    82,    38,
     152,   153,     5,     6,    43,    44,    43,    44,    31,    37,
       9,    27,    40,    38,    19,    38,    15,     6,     7,     8,
       9,    20,    21,    28,     4,    14,    37,    16,    17,    40,
      46,     6,     6,    37,    44,    38,     6,     7,     8,     9,
      39,    30,    31,    53,    41,     6,    16,    17,    58,    37,
      23,     6,    40,    26,     6,     7,     8,     9,     6,    29,
      30,    31,    14,    46,    16,    17,     6,     7,     8,     9,
       3,    10,    10,     6,    14,    38,    16,    17,    30,    31,
       6,     6,     6,     7,     8,     9,     6,     6,    12,    38,
      30,    31,    16,    17,     6,     7,     8,     9,    13,    13,
      12,    37,    37,    37,    16,    17,    30,    31,    39,     6,
       6,     7,     8,     9,    98,    24,    25,    11,    30,    31,
      16,    17,    11,    32,    33,    34,    35,    36,   137,    40,
      39,    39,    41,    42,    30,    31,    45,    24,    25,    -1,
      -1,    -1,    -1,    -1,    -1,    32,    33,    34,    35,    36,
      -1,    24,    25,    -1,    41,    42,    -1,    -1,    45,    32,
      33,    34,    35,    36,    24,    25,    -1,     9,    41,    42,
      -1,    -1,    45,    15,    34,    35,    36,    -1,    20,    21,
      22,    41,    42,    -1,    -1,    45
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    18,    48,    50,     0,     9,    15,    20,    21,    22,
      51,    52,    59,    60,    61,     6,    19,    28,    53,     6,
       6,     6,    37,    49,     6,    37,    40,    37,    40,    37,
      40,    62,    54,     6,     7,     8,     9,    14,    16,    17,
      30,    31,    63,    38,    23,    26,     4,     5,     6,    38,
      76,    77,    69,    74,     6,    43,    44,     6,    43,    44,
      76,     6,     6,    37,    55,     3,     6,    31,    76,    77,
      78,    41,    76,    24,    25,    32,    33,    34,    35,    36,
      41,    42,    45,    66,    71,    76,     6,    77,     6,     6,
      77,     6,    78,    64,     9,    15,    20,    21,    39,    56,
      27,     6,    46,    76,    39,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    10,    10,    70,    75,    38,
       6,     6,     6,    50,    65,    78,    42,    62,    62,    13,
      13,    57,    58,    37,    37,    37,    62,    38,    67,    72,
      62,    62,    39,     6,    29,    57,    11,    11,    14,    14,
      40,    39,    68,    73,    62,    62,    12,    12
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
#line 162 "flash.y"
    {	gen_code( DATA, data_location() - 1 );
					reset_block();								;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 165 "flash.y"
    {	gen_code( HALT, 0 ); YYACCEPT;				;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 172 "flash.y"
    {	
		install( (yyvsp[(3) - (4)].id) , 1, block_offset);  
		gen_code_bool_str(DEF, "0");
	;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 177 "flash.y"
    {	
		install( (yyvsp[(3) - (4)].id) , 0, block_offset);  
		gen_code_bool_str(DEF, "true");
	;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 182 "flash.y"
    {	
		install( (yyvsp[(3) - (4)].id) , 2, block_offset);  
		gen_code_bool_str(DEF, "str");
	;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 187 "flash.y"
    { 
		install((yyvsp[(2) - (3)].id), 4, block_offset); 
		gen_code_bool_str(DEF, "stk");  
	;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 196 "flash.y"
    { 
		block_in(); 						/*	increment block scope  */
		gen_fun( FUN_INIT, (yyvsp[(2) - (2)].id)); 
		install((yyvsp[(2) - (2)].id), 3, block_offset); 
		activate((yyvsp[(2) - (2)].id), block_offset);
	;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 206 "flash.y"
    { 
    	gen_code( FUN_EN, 0);
    ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 215 "flash.y"
    {	
		install( (yyvsp[(2) - (3)].id) , 1, block_offset );
		context_check(PARA_INT , (yyvsp[(2) - (3)].id), -1);
		add_para_to_as(block_offset,"PARA_INT");
		//printf("argi : %d\n",fun_offset);					
	;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 222 "flash.y"
    {	
		install( (yyvsp[(2) - (3)].id) , 0, block_offset );
		context_check(PARA_BOOL , (yyvsp[(2) - (3)].id), -1);	
		add_para_to_as(block_offset,"PARA_BOOL");	
		//printf("argb : %d\n",fun_offset)	;			
	;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 229 "flash.y"
    {	
		install( (yyvsp[(2) - (3)].id) , 2, block_offset );
		context_check(PARA_STR , (yyvsp[(2) - (3)].id), -1);
		add_para_to_as(block_offset,"PARA_STR");
		//printf("args : %d\n",fun_offset)		;				
	;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 238 "flash.y"
    { 
		arg_offset++;
		argument_check((yyvsp[(2) - (2)].id),arg_offset);				
	;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 245 "flash.y"
    {	
		arg_offset++;	
		argument_check((yyvsp[(2) - (3)].id),arg_offset);			
	;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 253 "flash.y"
    {	
		install( (yyvsp[(2) - (3)].id) , 1, block_offset); 
		gen_code_bool_str(DEF, "0");			
	;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 260 "flash.y"
    {	
		install( (yyvsp[(2) - (3)].id) , 0, block_offset);
		gen_code_bool_str(DEF, "true");			
	;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 267 "flash.y"
    {	
		install( (yyvsp[(2) - (3)].id) , 2, block_offset);
		gen_code_bool_str(DEF, "str");			
	;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 277 "flash.y"
    { 
		context_check(ADDSTK, (yyvsp[(1) - (5)].id), 4);      
	;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 281 "flash.y"
    { 
		context_check(REMSTK, (yyvsp[(3) - (4)].id), 4); 
		context_check(STORE, (yyvsp[(1) - (4)].id) , 1);     
	;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 286 "flash.y"
    { 
		context_check( POP, (yyvsp[(2) - (2)].id) ,-1); 						
	;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 290 "flash.y"
    { 
		context_check_fun(FUN_CALL, (yyvsp[(2) - (2)].id), 3);		
	;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 294 "flash.y"
    {
		if(arg_offset != as[fun_offset-1].q.count)
		yyerror( " Number of parameters don't match!");
		arg_offset = 0;		
	;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 300 "flash.y"
    { 
		context_check_fun(FUN_CALL, (yyvsp[(4) - (4)].id), 3);		
	;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 304 "flash.y"
    {
		if(arg_offset != as[fun_offset-1].q.count)
		yyerror( " Number of parameters don't match!");
		arg_offset = 0;
		context_check( STORE, (yyvsp[(1) - (8)].id) , 1);		
	;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 311 "flash.y"
    {    
		context_check( READ_INT, (yyvsp[(2) - (2)].id) , 1);				
	;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 315 "flash.y"
    {    
		context_check( READ_BOL, (yyvsp[(3) - (3)].id) , 0);			
	;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 319 "flash.y"
    {    
		context_check( READ_STR, (yyvsp[(3) - (3)].id) , 2);			
	;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 323 "flash.y"
    {	
		gen_code( WRITE_INT, 1 );							
	;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 327 "flash.y"
    {	
		gen_code( WRITE_BOL, 0 );						
	;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 331 "flash.y"
    {	
		gen_code( WRITE_STR, 2 );						
	;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 335 "flash.y"
    { 
		context_check( STORE, (yyvsp[(1) - (3)].id) , 1);   		
	;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 339 "flash.y"
    { 
		context_check( STORE, (yyvsp[(1) - (3)].id) , 0);   		
	;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 343 "flash.y"
    { 
		context_check( STORE, (yyvsp[(1) - (3)].id) , 2);   		
	;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 350 "flash.y"
    {	
		(yyvsp[(1) - (2)].lbls) = (struct lbs *) newlblrec();
		(yyvsp[(1) - (2)].lbls)->for_jmp_false = reserve_loc(); 					
	;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 355 "flash.y"
    { 
		(yyvsp[(1) - (5)].lbls)->for_goto = reserve_loc(); 					
	;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 359 "flash.y"
    {
		back_patch( (yyvsp[(1) - (7)].lbls)->for_jmp_false, JMP_FALSE,gen_label() ); 								
	;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 364 "flash.y"
    { 
	  	back_patch( (yyvsp[(1) - (10)].lbls)->for_goto, GOTO, gen_label() ); 		
	;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 368 "flash.y"
    { 
		(yyvsp[(1) - (1)].lbls) = (struct lbs *) newlblrec();
		(yyvsp[(1) - (1)].lbls)->for_goto = gen_label(); 							
	;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 373 "flash.y"
    { 
		(yyvsp[(1) - (3)].lbls)->for_jmp_false = reserve_loc();					
	;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 379 "flash.y"
    { 
		gen_code( GOTO, (yyvsp[(1) - (7)].lbls)->for_goto );
		back_patch( (yyvsp[(1) - (7)].lbls)->for_jmp_false, JMP_FALSE, gen_label() );									
	;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 388 "flash.y"
    {	
		(yyvsp[(1) - (2)].lbls) = (struct lbs *) newlblrec();
		(yyvsp[(1) - (2)].lbls)->for_jmp_false = reserve_loc(); 					
	;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 393 "flash.y"
    {
		(yyvsp[(1) - (5)].lbls)->for_goto = reserve_loc(); 					
	;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 397 "flash.y"
    { 
		back_patch( (yyvsp[(1) - (7)].lbls)->for_jmp_false, JMP_FALSE, gen_label() ); 								
	;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 402 "flash.y"
    { 
		back_patch( (yyvsp[(1) - (10)].lbls)->for_goto, GOTO, gen_label() ); 		
	;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 406 "flash.y"
    { 
		(yyvsp[(1) - (1)].lbls) = (struct lbs *) newlblrec();
		(yyvsp[(1) - (1)].lbls)->for_goto = gen_label(); 							
	;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 411 "flash.y"
    { 
		(yyvsp[(1) - (3)].lbls)->for_jmp_false = reserve_loc();			
	;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 417 "flash.y"
    { 
		gen_code( GOTO, (yyvsp[(1) - (7)].lbls)->for_goto );
		back_patch( (yyvsp[(1) - (7)].lbls)->for_jmp_false,JMP_FALSE,gen_label() );									
	;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 422 "flash.y"
    { gen_code( LD_INT, (yyvsp[(1) - (1)].intval) );							;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 423 "flash.y"
    { context_check( LD_VAR, (yyvsp[(1) - (1)].id) , -1);					;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 424 "flash.y"
    { gen_code( LT, 0 );								;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 425 "flash.y"
    { gen_code( EQ, 0 );								;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 426 "flash.y"
    { gen_code( GT, 0 );								;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 427 "flash.y"
    { gen_code( GTEQ, 0 );								;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 428 "flash.y"
    { gen_code( LTEQ, 0 );								;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 429 "flash.y"
    { gen_code( ADD, 0 );								;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 430 "flash.y"
    { gen_code( SUB, 0 );								;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 431 "flash.y"
    { gen_code( MULT, 0 );								;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 432 "flash.y"
    { gen_code( DIV, 0 );								;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 433 "flash.y"
    { gen_code( PWR, 0 );								;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 436 "flash.y"
    { gen_code_bool_str( LD_BOL, (yyvsp[(1) - (1)].boolval) );					;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 437 "flash.y"
    { context_check( LD_VAR, (yyvsp[(1) - (1)].id) ,-1);					;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 439 "flash.y"
    { gen_code_bool_str( LD_STR, (yyvsp[(1) - (1)].strval) );					;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 440 "flash.y"
    { context_check( LD_VAR, (yyvsp[(1) - (1)].id) ,-1);					;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 441 "flash.y"
    { gen_code(ADD_STR, 0);								;}
    break;



/* Line 1455 of yacc.c  */
#line 2205 "flash.tab.c"
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
#line 443 "flash.y"

/*=========================================================================
MAIN
=========================================================================*/
main( int argc, char *argv[] )
{   extern FILE *yyin;
	++argv; --argc;
	
	if (argv[0] == NULL || strstr(argv[0], ".fl") == NULL) {
		printf ( "Input file is not a Flash file \n" );
		exit(1);
	}
	
	yyin = fopen( argv[0], "r" );
	
	/*yydebug = 1;*/
	errors = 0;
	yyparse ();
	printf ( "Parse Completed\n" );
	if ( errors == 0 )
	{	
		char *outFile = malloc(strlen(argv[0])+strlen(".cls")+1);
		strcpy(outFile, argv[0]);
		strcat(outFile, ".cls");
		FILE *fp = fopen(outFile,"w+");
		print_code (fp);
		fclose(fp);
	}
}
/*=========================================================================
YYERROR
=========================================================================*/
yyerror ( char *s ) /* Called by yyparse on error */
{
errors++;
printf ("Line : %d -- Error in Semantics : %s \n", yylineno, s);
exit(1);
}
/**************************** End Grammar File ***************************/

