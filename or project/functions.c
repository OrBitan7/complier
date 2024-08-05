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
#include "functions.h"
extern char *yytext;

// if (getTyp(var) != Collection)
// {
//     sprintf(msg, "%s not defined as a collection", var);
//     yyerror(msg);
// }

//	===	Code Generation Functions	===========================================
// Generate a definition for a variable
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
char *GenerateColAssign(char *input)
{
    char msg[32];
    char *result;
    if ((input[0] != '\"') && getTyp(input) != Collection)
    {
        sprintf(msg, "%s not defined as a collection", input);
        yyerror(msg);
    }

    if (input[0] == '\"')
    {
        result = malloc(18);
        strcpy(result, "make_collection({");
        if (input[strlen(input) - 1] == '\"')
        {
            input[strlen(input) - 1] = '\0';
        }
        char *temp = malloc(strlen(input) + 1);
        strcpy(temp, input);
        char *token;
        token = strtok(temp + 1, "@");
        char *comma = "\0";
        int i = 1;
        do
        {
            if (token)
            {
                result = (char *)realloc(result, (strlen(result) + 3 + strlen(token) + strlen(comma)) * sizeof(char));
                if (i != 1)
                {
                    strcat(result, comma);
                }
                strcat(result, "\"");
                strcat(result, token);
                strcat(result, "\"");
                i = 2;
            }
            comma = ",";
            token = strtok(NULL, "@");
        } while (token);
        free(temp);
        result = (char *)realloc(result, (strlen(result) + 2) * sizeof(char));
        strcat(result, "})");
    }
    else
    {
        result = strdup(input);
    }
    return result;

}

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

void CollectionPlusCollection(char *varName, char *remove_strint)
{
}

char *concatenate_strings(const char *first, char middle, const char *last)
{
    size_t length = strlen(first) + 1 + strlen(last); 
    char *result = (char *)malloc(length + 1);
    if (!result)
        printf("Error: failed to allocate memory\n");

    result[0] = '\0';

    strcat(result, first);
    int temp = strlen(result);
    result[temp] = middle;  
    result[temp + 1] = '\0'; 
    strcat(result, last);
    result[strlen(result)] = '\0'; 
    return result;
}