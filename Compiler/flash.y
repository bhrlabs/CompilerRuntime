%{/*************************************************************************
Compiler for the Simple language
***************************************************************************/
/*=========================================================================
C Libraries, Symbol Table, Code Generator & other C code
=========================================================================*/
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
#define YYDEBUG 1
/* For Debugging														*/
int errors;
/* Error Count*/
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
install ( char *sym_name ,int type)
{
	symrec *s;
	s = getsym (sym_name);
	if (s == 0)
		s = putsym (sym_name,type);
	else { errors++;
		printf( "%s is already defined\n", sym_name );
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
		printf( "%s", sym_name );
		printf( "%s\n", " is an undeclared identifier" );
		}
	else if (type != -1 && identifier->type != type) {
		printf( "%s", sym_name );
		printf( "%s\n", " type error!" );
		}
	else gen_code( operation, identifier->offset );
}
/*=========================================================================
							SEMANTIC RECORDS
=========================================================================*/
%}
%union semrec							/* The Semantic Records*/
{
int	intval;								/* Integer value */
char *id;								/* Identifiers	*/
struct lbs *lbls;						/* For backpatching	*/
char *boolval;	
char *strval;						
}
/*=========================================================================
								TOKENS
=========================================================================*/
%start program
%token <strval> STRING					/* Flash string */
%token <boolval> BOOLEAN					/* Flash boolean */
%token <intval> NUMBER					/* Flash integer */
%token <id> IDENTIFIER								/* Flash identifier */
%token <lbls> IF WHILE								/* For backpatching labels */
%token SKIP THEN ELSE FI DO END
%token INTEGER READ WRITE LET IN BOOLE STR STACK
%token ASSGNOP LEQ GEQ ONTO OUTFROM
%token FUN END_FUN RETURN CALL
/*=========================================================================
							OPERATOR PRECEDENCE
=========================================================================*/
%left '-' '+'
%left '*' '/'
%right '^'
/*=========================================================================
					GRAMMAR RULES for the Simple language
=========================================================================*/
%%
program : 	LET
				declaration
				functions
			IN	{	gen_code( DATA, data_location() - 1 );				}
				commands
			END {	gen_code( HALT, 0 ); YYACCEPT;						}
;
declaration : /* empty*/
	| declaration declarations
;	
declarations : SKIP
	| INTEGER id_seqi IDENTIFIER ';' {	install( $3 , 1);  gen_code_bool(DEF, "0");}
	| BOOLE id_seqb IDENTIFIER ';' {	install( $3 , 0);  gen_code_bool(DEF, "true");}
	| STR id_seqs IDENTIFIER ';' {	install( $3 , 2);  gen_code_bool(DEF, "str");}
	| STACK IDENTIFIER ';' { install($2, 4); gen_code_bool(DEF, "stk");  }
;
functions : /* empty */
	| functions fun
;
fun : FUN IDENTIFIER { gen_fun( FUN_INIT, $2); } 
		'(' parameter ')' 
		declaration
		commands
      END_FUN { gen_code( FUN_EN, 0); } 
;
parameter : /* empty */ 
	| parameter parameters
;
parameters : SKIP
	| INTEGER IDENTIFIER ';' {	install( $2 , 1);					}
	| BOOLE IDENTIFIER ';' {	install( $2 , 0);					}
	| STR IDENTIFIER ';' {	install( $2 , 2);						}
;
arguments : /* empty */
	| argument IDENTIFIER	{ context_check(PARA_INT , $2,-1);				}
;
argument : /* empty */
	| argument IDENTIFIER ',' {	context_check(PARA_INT , $2,-1);			}
;

id_seqi : /* empty */
	| id_seqi IDENTIFIER ',' {	install( $2 , 1); gen_code_bool(DEF, "0");			}
;
id_seqb : /* empty */
	| id_seqb IDENTIFIER ',' {	install( $2 , 0); gen_code_bool(DEF, "true");			}
;
id_seqs : /* empty */
	| id_seqs IDENTIFIER ',' {	install( $2 , 2); gen_code_bool(DEF, "str");			}
;
commands : /* empty */
	| commands command ';'
;
command : SKIP
	| IDENTIFIER ONTO '<' exp_int '>' { context_check(ADDSTK, $1, 4);      }
	| IDENTIFIER OUTFROM '<' exp_int '>' { context_check(REMSTK, $1, 4);      }
	| RETURN IDENTIFIER { context_check( POP, $2 ,-1); 						}
	| CALL IDENTIFIER'(' arguments ')' { 		}
	| READ IDENTIFIER {    context_check( READ_INT, $2 , 1);				}
	| READ '#' IDENTIFIER {    context_check( READ_BOL, $3 , 0);			}
	| READ '@' IDENTIFIER {    context_check( READ_STR, $3 , 2);			}
	| WRITE exp_int {	gen_code( WRITE_INT, 1 );							}
	| WRITE '#' exp_bol {	gen_code( WRITE_BOL, 0 );						}
	| WRITE '@' exp_bol {	gen_code( WRITE_BOL, 2 );						}
	| IDENTIFIER ASSGNOP exp_int { context_check( STORE, $1 , 1);   		}
	| IDENTIFIER ASSGNOP exp_bol { context_check( STORE, $1 , 0);   		}
	| IDENTIFIER ASSGNOP exp_str { context_check( STORE, $1 , 2);   		}	
	| IF exp_int	{	$1 = (struct lbs *) newlblrec();
					$1->for_jmp_false = reserve_loc(); 					}
	  THEN commands	{ $1->for_goto = reserve_loc(); 					}
	  ELSE			{ back_patch( $1->for_jmp_false,
							JMP_FALSE,
							gen_label() ); 								}

		commands
	  FI		{ back_patch( $1->for_goto, GOTO, gen_label() ); 		}	
	| WHILE		{ $1 = (struct lbs *) newlblrec();
				  $1->for_goto = gen_label(); 							}


		exp_int		{ $1->for_jmp_false = reserve_loc();					}

	DO
		commands
	END			{ gen_code( GOTO, $1->for_goto );
				  back_patch( $1->for_jmp_false,
						JMP_FALSE,
						gen_label() );									}
	| IF exp_bol	{	$1 = (struct lbs *) newlblrec();
					$1->for_jmp_false = reserve_loc(); 					}
	  THEN commands	{ $1->for_goto = reserve_loc(); 					}
	  ELSE			{ back_patch( $1->for_jmp_false,
							JMP_FALSE,
							gen_label() ); 								}

		commands
	  FI		{ back_patch( $1->for_goto, GOTO, gen_label() ); 		}	
	| WHILE		{ $1 = (struct lbs *) newlblrec();
				  $1->for_goto = gen_label(); 							}


		exp_bol		{ $1->for_jmp_false = reserve_loc();					}

	DO
		commands
	END			{ gen_code( GOTO, $1->for_goto );
				  back_patch( $1->for_jmp_false,
						JMP_FALSE,
						gen_label() );									}
;
exp_int : NUMBER		{ gen_code( LD_INT, $1 );							}
	| IDENTIFIER	{ context_check( LD_VAR, $1 , -1);						}
	| exp_int '<' exp_int	{ gen_code( LT, 0 );								}
	| exp_int '=' exp_int	{ gen_code( EQ, 0 );								}
	| exp_int '>' exp_int	{ gen_code( GT, 0 );								}
	| exp_int GEQ exp_int	{ gen_code( GTEQ, 0 );								}
	| exp_int LEQ exp_int	{ gen_code( LTEQ, 0 );								}
	| exp_int '+' exp_int	{ gen_code( ADD, 0 );								}
	| exp_int '-' exp_int	{ gen_code( SUB, 0 );								}
	| exp_int '*' exp_int	{ gen_code( MULT, 0 );								}
	| exp_int '/' exp_int	{ gen_code( DIV, 0 );								}
	| exp_int '^' exp_int	{ gen_code( PWR, 0 );								}
	| '(' exp_int ')'
;
exp_bol :  BOOLEAN		{ gen_code_bool( LD_BOL, $1 );							}
	| IDENTIFIER	{ context_check( LD_VAR, $1 ,-1);							}
;
exp_str :  STRING		{ gen_code_bool( LD_BOL, $1 );							}
	| IDENTIFIER	{ context_check( LD_VAR, $1 ,-1);							}
	| exp_str '.' exp_str { gen_code(ADD_STR, 0);								}  
;
%%
/*=========================================================================
MAIN
=========================================================================*/
main( int argc, char *argv[] )
{   extern FILE *yyin;
	++argv; --argc;
	
	if (argv[0] == NULL || strstr(argv[0], ".fl") == NULL) {
		printf ( "Input file is not a Flash file" );
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
printf ("%s\n", s);
}
/**************************** End Grammar File ***************************/
