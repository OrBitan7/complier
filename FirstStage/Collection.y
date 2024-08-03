%{
void yyerror (char *s);
int yylex();
#include <stdio.h>     /* C declarations used in actions */
#include <stdlib.h>
#include <ctype.h>
%}

%union {char *str;}         /* Yacc definitions */
%token <str> t_STRING t_ID
%token t_IF_CMD t_ELSE_CMD t_FOR_CMD t_WHILE_CMD t_BIGGER_EQUAL t_LOWER_EQUAL t_EQUAL t_NOT t_COLLECTION_CMD t_SET_CMD t_INT_CMD t_STRING_CMD t_INPUT_CMD t_OUTPUT_CMD t_INT t_STRING t_ID



%%
/* descriptions of expected inputs     corresponding actions (in C) */
SENTENCE : t_STRING			//Place Holder

%%                     /* C code */


int main (void) {
	return yyparse ( );
}

