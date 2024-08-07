%{
void yyerror (char *s);
int yylex();
#include <stdio.h>     /* C declarations used in actions */
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "symTab.h"
#include "functions.h"
extern char* yytext;

FILE *outputFile, *inputFile;

//	===	YACC Helper Functions	============================

char* CopyStr(char* str)
{
    char *new, *p;

    if (str[0] == '\"') {               //Literal
        new = malloc(strlen(str));
        if ((p = strchr(str+1, '\"')))
            *p = '\0';
        strcpy(new, str);
        //printf("\t*Copy %s\n", str);	//DEBUG
    }
    else {
        new = malloc(strlen(str)+1);    //Variable Name
        strcpy(new, str);
        //printf("\t*Copy %s\n", str);	//DEBUG
    }

    return new;
}

char* AddStrToList(char* list, char* str)
{
    char *p;
    char *new = realloc(list, strlen(list)+strlen(str));
    strcat(new, "@");
    if ((p = strchr(str+1, '\"')))
        *p = '\0';
    strcat(new, str+1);
	return new;
}
char *AddToList(char *list, char *str)
{
    char *new = realloc(list, strlen(list) + strlen(str)+2);
    strcat(new, "@");
    strcat(new, str);
    return new;
}
static int idx=0;

void insert(char* varName, varType typ)
{	
    for (int i = 0; i < idx; i++)
    {
        if (strcmp(SymTable[i].name, varName) == 0)
        {
            yyerror("Variable already defined\n");
            return;
        }
    }
	SymTable[idx].name = malloc(strlen(varName)+1);
	strcpy(SymTable[idx].name, varName);
    SymTable[idx].typ = typ;
	//printf("\t*Insert \"%s\" in to symtab; typ:%d\n", varName, typ); //DEBUG
	++idx;
}

varType getTyp(char* var)
{
    for (int i=0 ; i<idx ; ++i)
        if (strcmp(SymTable[i].name, var)==0)
            return SymTable[i].typ;
    return 0;
}



%}

%union {char *str;
        int number;}         /* Yacc definitions */
%token <str> t_STRING t_ID t_INT
%token t_IF_CMD t_ELSE_CMD t_FOR_CMD t_WHILE_CMD t_BIGGER_EQUAL t_LOWER_EQUAL t_EQUAL t_NOT t_COLLECTION_CMD t_SET_CMD t_INT_CMD t_STRING_CMD t_INPUT_CMD t_OUTPUT_CMD t_LOWER t_BIGGER  
/* %type <str> STRING_LIST INT_LIST STRING_
%type <str> VAR COLLECTION VARS OPERATORCOLL  SET OPERATORSET LEN
%type <number> DECLERATION_CMD */


%%
/* descriptions of expected inputs     corresponding actions (in C) */
srog :				srog statement
    |				statement
statement:
                    declaration
    |               assignment
    |               operation_statement
    |               control
    |               io
    ;                                                
declaration :       t_INT_CMD identifier_list ';'
    |               t_STRING_CMD identifier_list ';'
    |               t_SET_CMD identifier_list ';'
    |               t_COLLECTION_CMD identifier_list ';'
    ;
assignment:
                    identifier '=' operation ';'
    ;
operation_statement:
                    operation ';'
    ;
operation:
    |               operation '+' expression
    |               operation '-' expression
    |               operation '*' expression
    |               operation '/' expression
    |               operation '&' expression
    |               '|' operation '|'
    |               expression
    ;
expression:
                    literal
    |               identifier
    |               '(' operation ')'
    ;
control:
                    t_IF_CMD '(' condition ')' statement
    |               t_IF_CMD '(' condition ')' block
    |               t_IF_CMD '(' condition ')' statement t_ELSE_CMD statement
    |               t_IF_CMD '(' condition ')' block t_ELSE_CMD block
    |               t_WHILE_CMD '(' condition ')' statement
    |               t_WHILE_CMD '(' condition ')' block
    |               t_FOR_CMD '(' identifier ':' identifier ')' statement
    |               t_FOR_CMD '(' identifier ':' identifier ')' block
    ;
condition:
                    operation t_BIGGER operation
    |               operation t_LOWER operation
    |               operation t_BIGGER_EQUAL operation
    |               operation t_LOWER_EQUAL operation
    |               operation t_EQUAL operation
    |               t_NOT operation
    |               operation
    ;
io:
                    t_INPUT_CMD t_STRING identifier ';'
    |               t_OUTPUT_CMD t_STRING operation ';'
    ;
block:
                    '{' statement_list '}'
    ;
statement_list:
                    statement
    |               statement_list statement
    ;
identifier:
                    t_ID
    ;
identifier_list:
                    identifier
    |               identifier_list ',' identifier
    ;
literal:
                    number_literal
    |               string_literal
    |               set_literal
    |               collection_literal
    ;
number_literal:
                    t_INT
    ;
INT_LIST:
                    t_INT
    |               INT_LIST ',' t_INT
    ;
STRING_LIST:
                    t_STRING
    |               STRING_LIST ',' t_STRING
    ;
string_literal:
                    t_STRING
    ;
set_literal:
                    '[' ']'
    |               '[' INT_LIST ']'
    ;
collection_literal:
                    '{' '}'
    |               '{' STRING_LIST '}'
    ;





/* OPERATOR :          OPERATORCOLL                                                {printf("%s\n",$1);}
    |               PRINT
    |               OPERATORSET                                                 {printf("%s\n",$1);}
    |               LEN                                                         {printf("%s\n",$1);}    
;
LEN :               '|' VAR '|'                                                 {VarSer_Collection($2);
                                                                                char* temp = concatenate_strings(NULL,'(',$2);
                                                                                
                                                                                $$ = concatenate_strings(temp,')',".size()");
                                                                               }
    |               '|' VAR '|' ';'                                             {VarSer_Collection($2);
                                                                                char* temp = concatenate_strings(NULL,'(',$2);
                                                                                 
                                                                                $$ = concatenate_strings(temp,')',".size();");
                                                                                }  
;
PRINT :		        t_OUTPUT_CMD STRING_  OPERATORCOLL ';'                      {GenerateOut($2, $3);}
    |       		t_OUTPUT_CMD STRING_  OPERATORSET ';'                       {GenerateOut($2, $3);}
    |       		t_OUTPUT_CMD STRING_  LEN ';'                               {GenerateOut($2, $3);}
;
OPERATORCOLL :		VAR '=' OPERATORCOLL ';'                                    {char* temp =  concatenate_strings($1,'=',$3);
                                                                                $$ = concatenate_strings(temp,';',NULL);}
	|				OPERATORCOLL '+' COLLECTION              					{$3=GenerateColAssign($3) ;$$ = concatenate_strings($1,'+',$3);}
	|				OPERATORCOLL '-' COLLECTION 					            {$3 =GenerateColAssign($3) ;$$ = concatenate_strings($1,'-',$3);}
	|				OPERATORCOLL '&' COLLECTION 					            {char* temp =GenerateColAssign($3) ;$3 = temp;  $$ = concatenate_strings($1,'*',$3);}
	|				OPERATORCOLL '-' STRING_  			                        {char* temp =GenerateColAssign($3) ;$3 = temp;  $$ = concatenate_strings($1,'-',$3);}
	|				OPERATORCOLL '+' STRING_  			                        {char* temp =GenerateColAssign($3) ;$3 = temp;  $$ = concatenate_strings($1,'+',$3);}
    |               COLLECTION 										            {$$ = GenerateColAssign($1);}
;
OPERATORSET :		VAR '=' OPERATORSET ';'                                    {char* temp =  concatenate_strings($1,'=',$3);
                                                                                $$ = concatenate_strings(temp,';',NULL);}
    |               SET										                    {$$ = GenerateSetAssign($1);}
	|				OPERATORSET '+' SET              	        				{$3 =GenerateSetAssign($3);  $$ = concatenate_strings($1,'+',$3);}
	|				OPERATORSET '+' t_INT {$3=concatenate_strings(NULL,'*',yytext); char* temp =GenerateSetAssign($3) ;$3 = temp;  $$ = concatenate_strings($1,'+',$3);}
	|				OPERATORSET '-' SET 		        			            {char* temp =GenerateSetAssign($3) ;$3 = temp;  $$ = concatenate_strings($1,'-',$3);}
	|				OPERATORSET '-' t_INT  {$3=concatenate_strings(NULL,'*',yytext); char* temp =GenerateSetAssign($3) ;$3 = temp;  $$ = concatenate_strings($1,'-',$3);}
	|				OPERATORSET '&' SET         					            {$3 =GenerateSetAssign($3);  $$ = concatenate_strings($1,'*',$3);}
;
STRING_ :           t_STRING                                                    {$$ = CopyStr(yytext);}
;
/* CONDITIONS :        CONDITIONS  CONDITION
    |               CONDITION 
CONDITION :         CONDITIONINT         
    |               CONDITIONCOLL
    |               CONDITIONSET
    |               CONDITIONSTR
CONDITIONINT : 
     
CONDITIONCOLL :     CONDITIONCOLL CONDITION_OP COLLECTION
    |               CONDITION
CONDITIONSET :
CONDITIONSTR : 
CONDITION_OP :       */

/* SET :		       
					'[' ']'														{$$ = "*";}
	|				'[' INT_LIST ']'											{$$ = concatenate_strings(NULL,'*',$2);}
    |                VAR															{if(getTyp($1)==Set)
                                                                                    $$=CopyStr($1);
                                                                                else {
                                                                                    yyerrok;  
                                                                                }}
;
COLLECTION :		VAR															{if(getTyp($1)==Collection)
                                                                                    $$=CopyStr($1);
                                                                                else
                                                                                    yyerrok;}
	|				'{' '}'														{$$ = "\"";}
	|				'{' STRING_LIST '}'											{$$ = $2;}
;
VARS :              VARS ',' VAR                                                {$$ = AddToList($1, $3);}
    |               VAR                                                         {$$ = $1}
;
VAR :				t_ID														{$$ = CopyStr(yytext)}
;
STRING_LIST :		STRING_LIST ',' t_STRING									{$$ = AddStrToList($1, yytext);}
	|				t_STRING													{$$ = CopyStr(yytext);}
;
INT_LIST :		    INT_LIST ',' t_INT									        {$$ = AddToList($1, yytext);}
	|				t_INT													    {$$ = CopyINT(yytext);}
; */ 

%%
extern int yylineno;

void yyerror(char *s) {
    fprintf(stderr, "Error: %s at line %d\n", s, yylineno);
}
int main(void) {


    outputFile = freopen("test.cpp", "w", stdout);
    if (outputFile == NULL) {
        fprintf(stderr, "Error opening output file.\n");
        return 1;
    }

    inputFile = freopen("INPUT.txt", "r", stdin);
    if (inputFile == NULL) {
        fprintf(stderr, "Error opening input file.\n");
        return 1;
    }

    fprintf(stdout, "#include <stdio.h>\n");
    fprintf(stdout, "#include <stdlib.h>\n");
    fprintf(stdout, "#include <string.h>\n");
    fprintf(stdout, "#include <iostream>\n");
    fprintf(stdout, "#include <string>\n");
    fprintf(stdout, "#include <set>\n\n");
    fprintf(stdout, "#include <initializer_list>\n\n");
    
    fprintf(stdout, "using namespace std;\n\n");

    fprintf(stdout, "//COLLECTION operators\n");
    fprintf(stdout, "set<string> make_collection(initializer_list<string> list) {\n");
    fprintf(stdout, "    return set<string>(list);\n");
    fprintf(stdout, "}\n");

    fprintf(stdout, "set<string> operator-(const set<string>& set1, const set<string>& set2) {\n");
    fprintf(stdout, "    set<string> result = set1;\n");
    fprintf(stdout, "    for (const string& elem : set2) {\n");
    fprintf(stdout, "        result.erase(elem);\n");
    fprintf(stdout, "    }\n");
    fprintf(stdout, "    return result;\n");
    fprintf(stdout, "}\n");
    
    fprintf(stdout, "set<string> operator+(const set<string>& set1, const set<string>& set2) {\n");
    fprintf(stdout, "    set<string> result = set1;\n");
    fprintf(stdout, "    result.insert(set2.begin(), set2.end());\n");
    fprintf(stdout, "    return result;\n");
    fprintf(stdout, "}\n");

    fprintf(stdout, "set<string> operator+(const set<string>& set1, const string& str) {\n");
    fprintf(stdout, "    set<string> result = set1;\n");
    fprintf(stdout, "    result.insert(str);\n");
    fprintf(stdout, "    return result;\n");
    fprintf(stdout, "}\n");

    fprintf(stdout, "set<string> operator*(const set<string>& set1, const set<string>& set2) {\n");
    fprintf(stdout, "    set<string> result;\n");
    fprintf(stdout, "    for (const string& elem : set1) {\n");
    fprintf(stdout, "        if (set2.find(elem) != set2.end()) {\n");
    fprintf(stdout, "            result.insert(elem);\n");
    fprintf(stdout, "        }\n");
    fprintf(stdout, "    }\n");
    fprintf(stdout, "    return result;\n");
    fprintf(stdout, "}\n");

    fprintf(stdout, "void printSetWithMessage(const set<string>& mySet, const string& message) {\n");
    fprintf(stdout, "    cout << message << \" {\";\n");
    fprintf(stdout, "    auto it = mySet.begin();\n");
    fprintf(stdout, "    if (it != mySet.end()) {\n");
    fprintf(stdout, "        cout << \"\\\"\" << *it << \"\\\"\";\n");
    fprintf(stdout, "        ++it;\n");
    fprintf(stdout, "    }\n");
    fprintf(stdout, "    while (it != mySet.end()) {\n");
    fprintf(stdout, "        cout << \", \\\"\" << *it << \"\\\"\";\n");
    fprintf(stdout, "        ++it;\n");
    fprintf(stdout, "    }\n");
    fprintf(stdout, "    cout << \"}\" << endl;\n");
    fprintf(stdout, "}\n");

    fprintf(stdout, "//SET operators\n");
    fprintf(stdout, "set<int> make_Set(initializer_list<int> list) {\n");
    fprintf(stdout, "    return set<int>(list);\n");
    fprintf(stdout, "}\n");

    fprintf(stdout, "set<int> operator-(const set<int>& set1, const set<int>& set2) {\n");
    fprintf(stdout, "    set<int> result = set1;\n");
    fprintf(stdout, "    for (const int& elem : set2) {\n");
    fprintf(stdout, "        result.erase(elem);\n");
    fprintf(stdout, "    }\n");
    fprintf(stdout, "    return result;\n");
    fprintf(stdout, "}\n");
    
    fprintf(stdout, "set<int> operator+(const set<int>& set1, const set<int>& set2) {\n");
    fprintf(stdout, "    set<int> result = set1;\n");
    fprintf(stdout, "    result.insert(set2.begin(), set2.end());\n");
    fprintf(stdout, "    return result;\n");
    fprintf(stdout, "}\n");

    fprintf(stdout, "set<int> operator+(const set<int>& set1, const int& str) {\n");
    fprintf(stdout, "    set<int> result = set1;\n");
    fprintf(stdout, "    result.insert(str);\n");
    fprintf(stdout, "    return result;\n");
    fprintf(stdout, "}\n");

    fprintf(stdout, "set<int> operator*(const set<int>& set1, const set<int>& set2) {\n");
    fprintf(stdout, "    set<int> result;\n");
    fprintf(stdout, "    for (const int& elem : set1) {\n");
    fprintf(stdout, "        if (set2.find(elem) != set2.end()) {\n");
    fprintf(stdout, "            result.insert(elem);\n");
    fprintf(stdout, "        }\n");
    fprintf(stdout, "    }\n");
    fprintf(stdout, "    return result;\n");
    fprintf(stdout, "}\n");

    fprintf(stdout, "void printSetWithMessage(const set<int>& mySet, const string& message) {\n");
    fprintf(stdout, "    cout << message << \" [\";\n");
    fprintf(stdout, "    auto it = mySet.begin();\n");
    fprintf(stdout, "    if (it != mySet.end()) {\n");
    fprintf(stdout, "        cout << *it ;\n");
    fprintf(stdout, "        ++it;\n");
    fprintf(stdout, "    }\n");
    fprintf(stdout, "    while (it != mySet.end()) {\n");
    fprintf(stdout, "        cout << \",\" << *it ;\n");
    fprintf(stdout, "        ++it;\n");
    fprintf(stdout, "    }\n");
    fprintf(stdout, "    cout << \"]\" << endl;\n");
    fprintf(stdout, "}\n");

    fprintf(stdout, "int main()\n");
    fprintf(stdout, "{\n");
    yyparse();

    fprintf(stdout, "}\n");
    if (fclose(outputFile) != 0) {
        fprintf(stderr, "Error closing output file.\n");
    }
    if (fclose(inputFile) != 0) {
        fprintf(stderr, "Error closing input file.\n");
    }

}
