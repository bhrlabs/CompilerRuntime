
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
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
/* Line 1676 of yacc.c  */
#line 128 "flash.y"
semrec
{

/* Line 1676 of yacc.c  */
#line 129 "flash.y"

int	intval;								/* Integer value */
char *id;								/* Identifiers	*/
struct lbs *lbls;						/* For backpatching	*/
char *boolval;	
char *strval;						



/* Line 1676 of yacc.c  */
#line 96 "flash.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


