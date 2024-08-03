#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Collection.tab.hpp"
#include <iostream>
extern int yylex();
extern int yylineno;
extern char* yytext;
extern int yyparse(void);
using namespace std;

void yyerror(char *s) { fprintf(stderr, "%s\n", s); }

int main(void)
{
    int tokenCode;
    while (tokenCode = yylex())
        printf("Token:%s code:%d\n", yytext, tokenCode);

    printf("\nThe End...\n");
    return yyparse();
}
