%{
#include "Collection.tab.h"
#include <stdlib.h>
#include <stdio.h>
void yyerror (char *s);
int yylex();
extern int yylineno;
%}

%option yylineno

%%
\{                      { printf("// Token: '{'\n"); return '{'; }
\}                      { printf("// Token: '}'\n"); return '}'; }
\[                      { printf("// Token: '['\n"); return '['; }
\]                      { printf("// Token: ']'\n"); return ']'; }
\(                      { printf("// Token: '('\n"); return '('; }
\)                      { printf("// Token: ')'\n"); return ')'; }
if                      { printf("// Token: 'if'\n"); return t_IF_CMD; }
else                    { printf("// Token: 'else'\n"); return t_ELSE_CMD; }
for                     { printf("// Token: 'for'\n"); return t_FOR_CMD; }
while                   { printf("// Token: 'while'\n"); return t_WHILE_CMD; }
\>=                     { printf("// Token: '>='\n"); return t_BIGGER_EQUAL; }
\<=                     { printf("// Token: '<='\n"); return t_LOWER_EQUAL; }
\>                      { printf("// Token: '>'\n"); return t_BIGGER; } 
\<                      { printf("// Token: '<'\n"); return t_LOWER; }
==                      { printf("// Token: '=='\n"); return t_EQUAL; }
\!                      { printf("// Token: '!'\n"); return t_NOT; }
collection              { printf("// Token: 'collection'\n"); return t_COLLECTION_CMD; }
set                     { printf("// Token: 'set'\n"); return t_SET_CMD; }
int                     { printf("// Token: 'int'\n"); return t_INT_CMD; }
str                     { printf("// Token: 'str'\n"); return t_STRING_CMD; }
input                   { printf("// Token: 'input'\n"); return t_INPUT_CMD; }
output                  { printf("// Token: 'output'\n"); return t_OUTPUT_CMD; }
[+-]?[1-9][0-9]*        { printf("// Token: 'int' = %s\n", yytext); return t_INT; }
\"[^\"]*\"              { printf("// Token: 'string' = %s\n", yytext); return t_STRING; }
[a-zA-Z][a-zA-Z0-9]*    { printf("// Token: 'ID' = %s\n", yytext); return t_ID; }
[-+=;,&\*\|\/\:]    { printf("// Token: 'symbol' = %c\n", yytext[0]); return yytext[0]; }
[ \t\n\r]                 { /* Ignore whitespace */ }
.                       { printf("// Unexpected character: %c\n", yytext[0]); yyerror("unexpected character"); }

%%
int yywrap (void) {return 1;}
