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
%token t_IF_CMD t_ELSE_CMD t_FOR_CMD t_WHILE_CMD t_BIGGER_EQUAL t_LOWER_EQUAL t_EQUAL t_NOT t_COLLECTION_CMD t_SET_CMD t_INT_CMD t_STRING_CMD t_INPUT_CMD t_OUTPUT_CMD   
%type <str> STRING_LIST INT_LIST
%type <str> VAR COLLECTION VARS OPERATORCOLL  SET OPERATORSET LEN
%type <number> DECLERATION_CMD


%%
/* descriptions of expected inputs     corresponding actions (in C) */
Prog :				SENTENCE
	|				Prog SENTENCE
SENTENCE :			DECLERATION
    |               OPERATOR
DECLERATION :       DECLERATION_CMD VARS ';'									{GenerateDef($1,$2);}
DECLERATION_CMD :   t_COLLECTION_CMD                                            {$$ = 1;}
    |               t_SET_CMD                                                   {$$ = 2;}
    |               t_INT_CMD                                                   {$$ = 3;}
    |               t_STRING_CMD                                                {$$ = 4;}

OPERATOR :          OPERATORCOLL                                                {printf("%s\n",$1);}
    |               PRINT_COLL
    |               PRINT_SET
    |               OPERATORSET                                                 {printf("%s\n",$1);}
    |               LEN                                                         {printf("%s\n",$1);}    

LEN :               '|' VAR '|'                                                 {VarSer_Collection($2);
                                                                                char* temp = concatenate_strings(NULL,'(',$2);
                                                                                free($2) ;
                                                                                $$ = concatenate_strings(temp,')',".size()");
                                                                                free(temp);}
    |               '|' VAR '|' ';'                                             {VarSer_Collection($2);
                                                                                char* temp = concatenate_strings(NULL,'(',$2);
                                                                                free($2) ;
                                                                                $$ = concatenate_strings(temp,')',".size();");
                                                                                free(temp);}  

PRINT_COLL :		t_OUTPUT_CMD t_STRING {$2=CopyStr(yytext);} COLLECTION ';'  {GenerateColOut($2, $4);}
PRINT_SET :		t_OUTPUT_CMD t_STRING {$2=CopyStr(yytext);} COLLECTION ';'  {GenerateColOut($2, $4);}

OPERATORCOLL :		VAR '=' OPERATORCOLL ';'                                    {char* temp =  concatenate_strings($1,'=',$3);free($3) ;
                                                                                $$ = concatenate_strings(temp,';',NULL);free(temp) ;}
	|				OPERATORCOLL '&' COLLECTION 					            {char* temp =GenerateColAssign($3) ;free($3);$3 = temp;  $$ = concatenate_strings($1,'*',$3);free($3);}
    |               OPERATORCOLL '(' OPERATORCOLL ')' OPERATORCOLL              
    |               COLLECTION 										            {$$ = GenerateColAssign($1); free($1);}
	|				OPERATORCOLL '+' COLLECTION              					{char* temp =GenerateColAssign($3) ;free($3);$3 = temp;  $$ = concatenate_strings($1,'+',$3);free($3);}
	|				OPERATORCOLL '+' t_STRING {$3=strdup(yytext);} 			    {char* temp =GenerateColAssign($3) ;free($3);$3 = temp;  $$ = concatenate_strings($1,'+',$3);free($3);}
	|				OPERATORCOLL '-' COLLECTION 					            {char* temp =GenerateColAssign($3) ;free($3);$3 = temp;  $$ = concatenate_strings($1,'-',$3);free($3);}
	|				OPERATORCOLL '-' t_STRING {$3=strdup(yytext);} 			    {char* temp =GenerateColAssign($3) ;free($3);$3 = temp;  $$ = concatenate_strings($1,'-',$3);free($3);}

OPERATORSET :		VAR '=' OPERATORSET ';'                                    {char* temp =  concatenate_strings($1,'=',$3);free($3) ;
                                                                                $$ = concatenate_strings(temp,';',NULL);free(temp) ;}
    |               OPERATORSET '(' OPERATORSET ')' OPERATORSET              
    |               SET										                    {$$ = GenerateSetAssign($1); free($1);}
	|				OPERATORSET '+' SET              	        				{char* temp =GenerateSetAssign($3) ;free($3);$3 = temp;  $$ = concatenate_strings($1,'+',$3);free($3);}
	|				OPERATORSET '+' t_INT {$3=strdup(yytext);} 			        {char* temp =GenerateSetAssign($3) ;free($3);$3 = temp;  $$ = concatenate_strings($1,'+',$3);free($3);}
	|				OPERATORSET '-' SET 		        			            {char* temp =GenerateSetAssign($3) ;free($3);$3 = temp;  $$ = concatenate_strings($1,'-',$3);free($3);}
	|				OPERATORSET '-' t_INT {$3=strdup(yytext);} 			        {char* temp =GenerateSetAssign($3) ;free($3);$3 = temp;  $$ = concatenate_strings($1,'-',$3);free($3);}
	|				OPERATORSET '&' SET         					            {char* temp =GenerateSetAssign($3) ;free($3);$3 = temp;  $$ = concatenate_strings($1,'*',$3);free($3);}

CONDITIONS :        CONDITIONS  CONDITION
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
CONDITION_OP :      

SET :		        VAR															{if(getTyp($1)==Set)
                                                                                    $$=CopyStr($1);}
	|				'[' ']'														{$$ = "*";}
	|				'[' INT_LIST ']'											{$$ = concatenate_strings(NULL,'*',$2); free($2);}

COLLECTION :		VAR															{if(getTyp($1)==Collection) 
                                                                                $$=CopyStr($1);}
	|				'{' '}'														{$$ = "\"";}
	|				'{' STRING_LIST '}'											{$$ = $2;}
VARS :              VARS ',' VAR                                                {$$ = AddToList($1, $3);}
    |               VAR                                                         {$$ = $1}
VAR :				t_ID														{$$ = CopyStr(yytext)}
STRING_LIST :		STRING_LIST ',' t_STRING									{$$ = AddStrToList($1, yytext);}
	|				t_STRING													{$$ = CopyStr(yytext);}
INT_LIST :		    INT_LIST ',' t_INT									    {$$ = AddToList($1, yytext);}
	|				t_INT													    {$$ = CopyINT(yytext);}


%%

void yyerror (char *s) {fprintf (stderr, "%s\n", s); exit(1);} 

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

    fprintf(stdout, "int main()\n");
    fprintf(stdout, "{\n");
    yyparse();

    fprintf(stdout, "}\n");
}