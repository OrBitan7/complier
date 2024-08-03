#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symTab.h"

void yyerror(char *s);
int yylex();
#include <stdio.h> /* C declarations used in actions */
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "symTab.h"

extern char *yytext;

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
// GenerateColDef done
void GenerateColDef(char *colVar)
{
    fprintf(stdout, "set<string> %s;\n", colVar);
    insert(colVar, Collection);
}
// GenerateColAssign done
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
// GenerateColOut done
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
// GenerateColUnion done
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
    printf("%s", string);
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
