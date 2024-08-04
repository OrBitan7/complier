%{
void yyerror (char *s);
int yylex();
#include <stdio.h>     /* C declarations used in actions */
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "symTab.h"

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
	//printf("\t*NewStrList:%s\n", new);	//DEBUG
	return new;
}

static int idx=0;

void insert(char* varName, varType typ)
{	
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


//	===	Code Generation Functions	===========================================
//GenerateColDef done
void GenerateColDef(char *colVar)
{
    fprintf(stdout, "set<string> %s;\n", colVar);
    insert(colVar, Collection);
}

//GenerateColAssign done
void GenerateColAssign(char *var, char *coll)
{
    char msg[32];

    if (getTyp(var) != Collection)
    {
        sprintf(msg, "%s not defined as a collection", var);
        yyerror(msg);
    }

    if ((coll[0] != '\"') && getTyp(coll) != Collection)
    {
        sprintf(msg, "%s not defined as a collection", coll);
        yyerror(msg);
    }

    fprintf(stdout, "{\n");
    if (coll[0] == '\"')
    {
        char *temp = malloc(strlen(coll) + 1);
        strcpy(temp, coll);
        char *token;
        token = strtok(temp + 1, "@");
        while (token)
        {
            fprintf(stdout, "%s.insert(\"%s\");\n", var, token);
            token = strtok(NULL, "@");
        }
        free(temp);
    }
    else
        fprintf(stdout, "%s = %s;\n", var, coll);

    fprintf(stdout, "}\n");
}

//GenerateColOut done
void GenerateColOut(char *str, char *coll)
{
    char msg[32];

    if ((coll[0] != '\"') && getTyp(coll) != Collection)
    {
        sprintf(msg, "%s not defined as a collection", coll);
        yyerror(msg);
    }
    printf("{ \n");
    fprintf(stdout, "   cout << %s\";\n", str); // Command to print 1st string

    fprintf(stdout, "   cout << \"{\";\n"); // Command to start collection

    if (coll[0] == '\"')
    {
        char *temp = malloc(strlen(coll) + 1);
        strcpy(temp, coll);
        char *token;
        token = strtok(temp + 1, "@");
        char *comma = "";
        do
        {
            if (token)
                fprintf(stdout, "   cout << \"%s%s\" ;\n", comma, token);
            comma = ", ";
            token = strtok(NULL, "@");
        } while (token);
        free(temp);
    }
    else
    {
        fprintf(stdout, "   bool first = true;\n");
        fprintf(stdout, "   for (const auto& item : %s) {\n", coll);
        fprintf(stdout, "       if (!first) {\n");
        fprintf(stdout, "           cout << \", \";\n");
        fprintf(stdout, "       }\n");
        fprintf(stdout, "      cout << item;\n");
        fprintf(stdout, "      first = false;\n");
        fprintf(stdout, "   }\n");
    }

    fprintf(stdout, "   cout << \"}\" << endl;\n"); // Command to end collection
    printf("}\n");
}

//GenerateColUnion
void GenerateColUnion(char *varResultName, char *varName, char *coll)
{
    char msg[32];

    if (getTyp(varResultName) != Collection)
    {
        sprintf(msg, "%s not defined as a collection", varResultName);
        yyerror(msg);
    }

    if (getTyp(varName) != Collection)
    {
        sprintf(msg, "%s not defined as a collection", varName);
        yyerror(msg);
    }

    if ((coll[0] != '\"') && getTyp(coll) != Collection)
    {
        sprintf(msg, "%s not defined as a collection", coll);
        yyerror(msg);
    }

    fprintf(stdout, "{\n");
    if (coll[0] == '\"')
    {
        fprintf(stdout, "   %s.insert(%s.begin(), %s.end());\n", varResultName, varName, varName);
        char *temp = malloc(strlen(coll) + 1);
        strcpy(temp, coll);
        char *token;
        token = strtok(temp + 1, "@");
        while (token)
        {
            fprintf(stdout, "   %s.insert(\"%s\");\n", varResultName, token);
            token = strtok(NULL, "@");
        }
        free(temp);
    }
    else
    {
        fprintf(stdout, "   %s.insert(%s.begin(), %s.end());\n", varResultName, varName, varName);
        fprintf(stdout, "   %s.insert(%s.begin(), %s.end());\n", varResultName, coll, coll);
    }
    fprintf(stdout, "}\n");
}
// GenerateColUnionWithString done
void GenerateColUnionWithString(char *varResultName, char *varName, char *string)
{
    char msg[32];
    if (getTyp(varResultName) != Collection)
    {
        sprintf(msg, "%s not defined as a collection", varResultName);
        yyerror(msg);
    }

    if (getTyp(varName) != Collection)
    {
        sprintf(msg, "%s not defined as a collection", varName);
        yyerror(msg);
    }

    if (string[0] != '\"')
    {
        fprintf(stdout, "{\n");
        fprintf(stdout, "   %s.insert(%s.begin(), \"%s.end());\n", varResultName, varName, varName);
        fprintf(stdout, "   %s.insert(%s\");\n", varResultName, string);
        fprintf(stdout, "}\n");
    }
    else
    {
        fprintf(stdout, "{\n");
        fprintf(stdout, "   %s.insert(%s.begin(), %s.end());\n", varResultName, varName, varName);
        fprintf(stdout, "   %s.insert(%s\");\n", varResultName, string);
        fprintf(stdout, "}\n");
    }
}
// GenerateColDifference done
void GenerateColDifference(char *varResultName, char *varName, char *coll)
{
    char msg[32];

    if (getTyp(varResultName) != Collection)
    {
        sprintf(msg, "%s not defined as a collection", varResultName);
        yyerror(msg);
    }

    if (getTyp(varName) != Collection)
    {
        sprintf(msg, "%s not defined as a collection", varName);
        yyerror(msg);
    }

    if ((coll[0] != '\"') && getTyp(coll) != Collection)
    {
        sprintf(msg, "%s not defined as a collection", coll);
        yyerror(msg);
    }

    fprintf(stdout, "{\n");
    fprintf(stdout, "   %s = %s;\n", varResultName, varName);
    if (coll[0] == '\"')
    {
        char *temp = malloc(strlen(coll) + 1);
        strcpy(temp, coll);
        char *token;
        token = strtok(temp + 1, "@");
        while (token)
        {
            fprintf(stdout, "   %s.erase(\"%s\");\n", varResultName, token);
            token = strtok(NULL, "@");
        }
        free(temp);
    }
    else
    {
        fprintf(stdout, "for (const auto& element : %s) {\n", coll);
        fprintf(stdout, "    %s.erase(element);\n", varResultName);
        fprintf(stdout, "}\n");
    }

    fprintf(stdout, "}\n");
}

void GenerateColDifferenceWithString(char *varResultName, char *varName, char *remove_strint)
{
    char msg[32];

    if (getTyp(varResultName) != Collection)
    {
        sprintf(msg, "%s not defined as a collection", varResultName);
        yyerror(msg);
    }

    if (getTyp(varName) != Collection)
    {
        sprintf(msg, "%s not defined as a collection", varName);
        yyerror(msg);
    }

    if (remove_strint[0] != '\"')
    {
        sprintf(msg, "%s not defined as a string", remove_strint);
        yyerror(msg);
    }

    fprintf(stdout, "{\n");
    fprintf(stdout, "   %s = %s;\n", varResultName, varName);
    if (remove_strint[0] == '\"')
    {
        fprintf(stdout, "   %s.erase(%s\");\n", varResultName, remove_strint);
    }
    else
    {
        fprintf(stdout, "    %s.erase(\"%s\");\n", varResultName, remove_strint);
    }

    fprintf(stdout, "}\n");
}


%}

%union {char *str;}         /* Yacc definitions */
%token <str> t_STRING t_ID
%token t_IF_CMD t_ELSE_CMD t_FOR_CMD t_WHILE_CMD t_BIGGER_EQUAL t_LOWER_EQUAL t_EQUAL t_NOT t_COLLECTION_CMD t_SET_CMD t_INT_CMD t_STRING_CMD t_INPUT_CMD t_OUTPUT_CMD t_INT  
%type <str> STRING_LIST
%type <str> VAR COLLECTION


%%
/* descriptions of expected inputs     corresponding actions (in C) */
Prog :				SENTENCE
	|				Prog SENTENCE
SENTENCE :			DECLERATION
    |               OPERATOR
DECLERATION :       t_COLLECTION_CMD VAR ';'									{GenerateColDef($2);}
OPERATOR :			VAR '=' COLLECTION ';'										{GenerateColAssign($1,$3);}
	|				t_OUTPUT_CMD t_STRING {$2=CopyStr(yytext);} COLLECTION ';'	{GenerateColOut($2, $4);}
	|				VAR '=' VAR '+' COLLECTION ';'								{GenerateColUnion($1, $3, $5);}
	|				VAR '=' VAR '+' t_STRING {$5=CopyStr(yytext);} ';'			{GenerateColUnionWithString($1, $3, $5);}
	|				VAR '=' VAR '-' COLLECTION ';'								{GenerateColDifference($1, $3, $5);}
	|				VAR '=' VAR '-' t_STRING {$5=CopyStr(yytext);} ';'			{GenerateColDifferenceWithString($1, $3, $5);}
COLLECTION :		VAR															{$$=CopyStr($1);}
	|				'{' '}'														{$$ = "\"";}
	|				'{' STRING_LIST '}'											{$$ = $2;}
VAR :				t_ID														{$$ = CopyStr(yytext)}
STRING_LIST :		STRING_LIST ',' t_STRING									{$$ = AddStrToList($1, yytext);}
	|				t_STRING													{$$ = CopyStr(yytext);}




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
    fprintf(stdout, "using namespace std;\n\n");
    fprintf(stdout, "int main()\n");
    fprintf(stdout, "{\n");

    yyparse();

    fprintf(stdout, "}\n");
}