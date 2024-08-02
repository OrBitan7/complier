#include <stdio.h>
#include "Collection.tab.h"

extern int yylex();
extern int yylineno;
extern char* yytext;

void yyerror (char *s) {fprintf (stderr, "%s\n", s);} 

int main(void)
{
    int tokenCode;
    while(tokenCode=yylex())
        printf("Token:%s code:%d\n", yytext, tokenCode);

    printf("\nThe End...\n");
}
