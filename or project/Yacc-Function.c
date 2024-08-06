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
        printf("//// \t*Copy %s\n", str); // DEBUG
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
char *AddToList(char *list, char *str)
{
    char *new = realloc(list, strlen(list) + strlen(str));
    strcat(new, "@");
    strcat(new, str);
    // printf("\t*NewStrList:%s\n", new);	//DEBUG
    return new;
}
static int idx = 0;

void insert(char *varName, varType typ)
{
    for (int i = 0; i < idx; i++)
    {
        if (strcmp(SymTable[i].name, varName) == 0)
        {
            yyerror("Variable already defined\n");
            return;
        }
    }
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
void GenerateDef(varType type, char *Vars)
{
    char *temp = malloc(strlen(Vars) + 1);
    strcpy(temp, Vars);
    char *token;
    token = strtok(temp, "@");
    while (token)
    {
        switch (type)
        {
        case Collection:
            fprintf(stdout, "set<string> %s;\n", token);
            break;
        case Set:
            fprintf(stdout, "set<int> %s;\n", token);
            break;
        case Int:
            fprintf(stdout, "int %s;\n", token);
            break;
        case String:
            fprintf(stdout, "string %s;\n", token);
            break;
        default:
            break;
        }
        insert(token, type);
        token = strtok(NULL, "@");
    }
    free(temp);
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
// GenerateColUnionWithString fix!!!!!!!!!!
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
        fprintf(stdout, "   %s.insert(%s.begin(), %s.end());\n", varResultName, varName, varName);
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
// GenerateColDifferenceWithString done
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

/////////////////////////////////////////////////////

//	===	Code Generation Functions	===========================================
void GenerateDef(varType type, char *Vars)
{
    char *temp = malloc(strlen(Vars) + 1);
    strcpy(temp, Vars);
    char *token;
    token = strtok(temp, "@");
    while (token)
    {
        switch (type)
        {
        case Collection:
            fprintf(stdout, "set<string> %s;\n", token);
            break;
        case Set:
            fprintf(stdout, "set<int> %s;\n", token);
            break;
        case Int:
            fprintf(stdout, "int %s;\n", token);
            break;
        case String:
            fprintf(stdout, "string %s;\n", token);
            break;
        default:
            break;
        }
        insert(token, type);
        token = strtok(NULL, "@");
    }
    free(temp);
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

// GenerateColUnion
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


lex:
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
[ \t\n]               {}
.                       {ECHO; yyerror ("unexpected character");}
