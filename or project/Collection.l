%{
#include "Collection.tab.h"
void yyerror (char *s);
int yylex();
%}
%%
\{                      {return '{';}
\}                      {return '}';}
\[                      {return '[';}
\]                      {return ']';}
\(                      {return '(';}
\)                      {return ')';}
if                      {return t_IF_CMD;}
else                    {return t_ELSE_CMD;}
for                     {return t_FOR_CMD;}
while                   {return t_WHILE_CMD;}
\>=                     {return t_BIGGER_EQUAL;}
\<=                     {return t_LOWER_EQUAL;}
==                      {return t_EQUAL;}
\!                      {return t_NOT;}
collection              {return t_COLLECTION_CMD;}
set                     {return t_SET_CMD;}
int                     {return t_INT_CMD;}
str                     {return t_STRING_CMD;}
input                   {return t_INPUT_CMD;}
output                  {return t_OUTPUT_CMD;}
[+-]?[1-9][0-9]*        {return t_INT;}
\"[^\"]*\"              {return t_STRING;}
[a-zA-Z][a-zA-Z0-9]*    {return t_ID;}
[-+=;,\>\<&\*\|\/\:]    {return yytext[0];}
[ \t\n]                 {}
.                       {ECHO; yyerror ("unexpected character");}

%%
int yywrap (void) {return 1;}
