%{
void yyerror (char *s);
int yylex();
#include <stdio.h>     /* C declarations used in actions */
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "symTab.h"

extern char* yytext;

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

// collection - collection:
char *RT_RemoveStrToCollection(char *collection, char *str)
{

	if (collection == NULL || str == NULL)
	{
		return collection;
	}
	

	char *pos = strstr(collection, str);
	if (pos != NULL)
	{
		printf("pos:%s\n", pos);
		printf("str:%s\n", str);
		printf("next:%c\n", pos[strlen(str)]);
		printf("beffor:%c\n", pos[-1]);
		int lenStr = strlen(str);
		int lenColl = strlen(collection);
		int lenRemain = lenColl - lenStr;
		fprintf(stdout, "itration\n");
		if (pos[strlen(str)] == '@')
		{
			lenStr++;
			memmove(pos, pos + lenStr , strlen(pos + lenStr) + 1);
		}
		else if (pos[-1] == '@')
		{
			lenStr++;
			pos--;
			memmove(pos, pos + lenStr, strlen(pos + lenStr) + 1);
		}
		else
		{
			memmove(pos, pos + lenStr, strlen(pos + lenStr) + 1);
		}

		collection = realloc(collection, lenRemain + 1);
	}

	return collection;
}

char *RT_DifferenceCollections(char *var, char *coll)
{
	char *temp = malloc(strlen(coll) + 1);
	strcpy(temp, coll);
	char *token;
	token = strtok(temp + 1, "@");
	do
	{
		if (token && (strstr(var, token) != NULL))
			var = RT_RemoveStrToCollection(var, token);
		token = strtok(NULL, "@");
	} while (token);
	free(temp);

	return var;
}
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
    if (coll[0] == '\"')
        fprintf(stdout, "char* unified = RT_DifferenceCollections(%s, \"\\%s\");\n", varName, coll);
    else
        fprintf(stdout, "char* unified = RT_DifferenceCollections(%s, %s);\n", varName, coll);

    fprintf(stdout, "int len = strlen(unified);\n");

    fprintf(stdout, "if (%s == NULL)	%s=malloc(len+1);\n", varResultName, varResultName);
    fprintf(stdout, "else	%s = realloc(%s,len+1);\n", varResultName, varResultName);

    fprintf(stdout, "strcpy(%s, unified);\n", varResultName);
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
SENTENCE :			t_COLLECTION_CMD VAR ';'				{GenerateColDef($2);}
	|				VAR '=' COLLECTION ';'					{GenerateColAssign($1,$3);}
	|				t_OUTPUT_CMD t_STRING {$2=CopyStr(yytext);} COLLECTION ';'			{GenerateColOut($2, $4);}
	|				VAR '=' VAR '+' COLLECTION ';'			{GenerateColUnion($1, $3, $5);}
	|				VAR '=' VAR '-' COLLECTION ';'			{GenerateColDifference($1, $3, $5);}
COLLECTION :		VAR										{$$=CopyStr($1);}
	|				'{' '}'									{$$ = "\"";}
	|				'{' STRING_LIST '}'						{$$ = $2;}
VAR :				t_ID									{$$ = CopyStr(yytext)}
STRING_LIST :		STRING_LIST ',' t_STRING				{$$ = AddStrToList($1, yytext);}
	|				t_STRING								{$$ = CopyStr(yytext);}
