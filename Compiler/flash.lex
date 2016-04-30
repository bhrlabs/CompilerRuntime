/*=========================================================================
TEAM : Team 31, Team Flash, Very Fast Much Wow.

Flash 5.0 : Block structured, Strongly Typed, Procedural Programming Language.

Members : Anant Srivastava
		  Bharat Singh
		  Wenbo Tian
		  Vidyaabharathi Vasudevan

Build Using : FLEX(2.6.0), BISON (GNU 3.0.4), C;		  

References : Compiler Construction using Flex and Bison,
						Anthony A. Aaby,
			 		email :	aabyan@wwc.edu
			 	  version of Feburary 25,2004.
	OPEN PUBLIC LISCENCE : https://opencontent.org/openpub
=========================================================================*/
/***************************************************************************
					Scanner for the Simple language
***************************************************************************/
%{
/*=========================================================================
				C-libraries and Token definitions
=========================================================================*/
#include <string.h>			/* for strdup */
/*#include <stdlib.h> */	/* for atoi */
#include "flash.tab.h" 	/* for token definitions and yylval */

%}
/*=========================================================================
							TOKEN Definitions
=========================================================================*/
DIGIT	[0-9]
ID		[a-z][a-z0-9]*
BOOL	[t][r][u][e]|[f][a][l][s][e]
STRIN	[\"][A-Za-z0-9\*\-\^\!\@\#\$\%\&\(\)\.\:\;\,\ ]+[\"]
%option yylineno
/*=========================================================================
	REGULAR EXPRESSIONS defining the tokens for the Simple language
=========================================================================*/
%%
":="		{ return(ASSGNOP); 	}
{DIGIT}+ 	{ yylval.intval = atoi( yytext );
			  return(NUMBER);	}
{BOOL}+ 	{ yylval.boolval = (char *) strdup(yytext);
			  return(BOOLEAN);	}	
{STRIN} 	{ yylval.strval = (char *) strdup(yytext);
			  return(STRING);	}			  
do			{ return(DO);		}
else		{ return(ELSE);		}
end			{ return(END);		}
fi			{ return(FI);		}
if			{ return(IF);		}
fun			{ return(FUN);		}
end_fun		{ return(END_FUN);	}
return		{ return(RETURN);	}
call		{ return(CALL);		}
"<="		{ return(LEQ);		}
">="		{ return(GEQ);		}
".onto"     { return(ONTO);		}
".outfrom"  { return(OUTFROM);	}
in			{ return(IN);		}
integer 	{ return(INTEGER); 	}
boolean		{ return(BOOLE);	}
string		{ return(STR);		}
stack		{ return(STACK);	}
let			{ return(LET);		}
read		{ return(READ);		}
skip		{ return(SKIP);		}
then		{ return(THEN);		}
while		{ return(WHILE);	}
write		{ return(WRITE);	}
{ID}		{ yylval.id = (char *) strdup(yytext);
			  return(IDENTIFIER);}
[ \t\n]+ /* eat up whitespace */
.			{ return(yytext[0]);}
%%
int yywrap(void){}
/************************** End Scanner File *****************************/
