#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symTab.h"

//	===	YACC Helper Functions	============================

char *CopyStr(char *str)
{
    char *new, *p;

    if (str[0] == '\"')
    { // Literal
        new = malloc(strlen(str));
        if ((p = strchr(str + 1, '\"')))
            *p = '\0';
        strcpy(new, str);
        // printf("\t*Copy %s\n", str);	//DEBUG
    }
    else
    {
        new = malloc(strlen(str) + 1); // Variable Name
        strcpy(new, str);
        // printf("\t*Copy %s\n", str);	//DEBUG
    }

    return new;
}

char *AddStrToList(char *list, char *str)
{
    char *p;
    char *new = realloc(list, strlen(list) + strlen(str));
    strcat(new, "@");
    if ((p = strchr(str + 1, '\"')))
        *p = '\0';
    strcat(new, str + 1);
    // printf("\t*NewStrList:%s\n", new);	//DEBUG
    return new;
}

static int idx = 0;

void insert(char *varName, varType typ)
{
    SymTable[idx].name = malloc(strlen(varName) + 1);
    strcpy(SymTable[idx].name, varName);
    SymTable[idx].typ = typ;
    // printf("\t*Insert \"%s\" in to symtab; typ:%d\n", varName, typ); //DEBUG
    ++idx;
}

varType getTyp(char *var)
{
    for (int i = 0; i < idx; ++i)
        if (strcmp(SymTable[i].name, var) == 0)
            return SymTable[i].typ;
    return 0;
}
//	===	Code Generation Functions	===========================================

void GenerateColDef(char *colVar)
{
    fprintf(stdout, "char* %s=NULL;\n", colVar);
    insert(colVar, Collection);
}

void GenerateSetDef(char *setVar)
{
    fprintf(stdout, "char* %s=NULL;\n", setVar);
    insert(setVar, Set);
}

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
    fprintf(stdout, "int len;\n");

    if (coll[0] == '\"')
        fprintf(stdout, "len = strlen(\"\\%s\");\n", coll);
    else
        fprintf(stdout, "len = strlen(%s);\n", coll);

    fprintf(stdout, "if (%s == NULL) %s=malloc(len+1);\n", var, var);
    fprintf(stdout, "else 	%s=realloc(%s, len+1);\n", var, var);

    if (coll[0] == '\"')
        fprintf(stdout, "strcpy(%s,\"\\%s\");\n", var, coll);
    else
        fprintf(stdout, "strcpy(%s, %s);\n", var, coll);

    fprintf(stdout, "}\n");
}

void GenerateColOut(char *str, char *coll)
{
    char msg[32];

    if ((coll[0] != '\"') && getTyp(coll) != Collection)
    {
        sprintf(msg, "%s not defined as a collection", coll);
        yyerror(msg);
    }

    fprintf(stdout, "printf(%s \");\n", str); // Command to print 1st string

    fprintf(stdout, "printf(\"{\");\n"); // Command to start collection

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
                fprintf(stdout, "printf(\"%s%s\");\n", comma, token);
            comma = ", ";
            token = strtok(NULL, "@");
        } while (token);
        free(temp);
    }
    else
    {
        fprintf(stdout, "{\n");
        fprintf(stdout, "char* temp = malloc(strlen(%s)+1);\n", coll);
        fprintf(stdout, "strcpy(temp, %s);\n", coll);
        fprintf(stdout, "char *token;\n");
        fprintf(stdout, "token = strtok(temp+1, \"@\");\n");
        fprintf(stdout, "char* comma=\"\";\n");
        fprintf(stdout, "do {\n");
        fprintf(stdout, "\tif (token) printf(\"%%s%%s\", comma, token);\n");
        fprintf(stdout, "\tcomma=\", \";\n");
        fprintf(stdout, "\ttoken = strtok(NULL, \"@\");\n");
        fprintf(stdout, "} while (token);\n");
        fprintf(stdout, "free(temp);\n");
        fprintf(stdout, "}\n");
    }

    fprintf(stdout, "printf(\"}\\n\");\n"); // Command to end collection
}

char *RT_unifyCollections(char *var, char *coll);
char *RT_DifferenceCollections(char *var, char *coll);
char *RT_addStrToCollection(char *collection, char *str);

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
void GenerateColUnify(char *varResultName, char *varName, char *coll)
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
        fprintf(stdout, "char* unified = RT_unifyCollections(%s, \"\\%s\");\n", varName, coll);
    else
        fprintf(stdout, "char* unified = RT_unifyCollections(%s, %s);\n", varName, coll);

    fprintf(stdout, "int len = strlen(unified);\n");

    fprintf(stdout, "if (%s == NULL)	%s=malloc(len+1);\n", varResultName, varResultName);
    fprintf(stdout, "else	%s = realloc(%s, strlen(%s)+len+1);\n", varResultName, varResultName, varResultName);

    fprintf(stdout, "strcpy(%s, unified);\n", varResultName);
    fprintf(stdout, "}\n");
}

int main()
{

}