#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Collection.tab.h"

extern int yylex();
extern int yylineno;
extern char* yytext;
extern int yyparse(void);

void yyerror (char *s) {fprintf (stderr, "%s\n", s); exit(1);} 

// int main(void)
// {
//     fprintf(stdout, "#include <stdio.h>\n");
//     fprintf(stdout, "#include <stdlib.h>\n");
//     fprintf(stdout, "#include <string.h>\n");
//     fprintf(stdout, "#include <iostream>\n");
//     fprintf(stdout, "#include <string>\n");
//     fprintf(stdout, "#include <set>\n\n");
//     fprintf(stdout, "using namespace std;\n\n");
//     fprintf(stdout, "int main()\n");
//     fprintf(stdout, "{\n");

//     yyparse();

//     fprintf(stdout, "}\n");
//     return 0;
// }
