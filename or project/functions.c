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

void GenerateOut(char *str, char *element)
{
    printf("printSetWithMessage(%s, \"%s\");\n", element, str);
}

char *CopyINT(char *str)
{
    char *new, *p;
    new = malloc(strlen(str) + 2);
    strcpy(new, str);
    // printf("\tCopy: %s\n", str);	//DEBUG
    // new = concatenate_strings(NULL, '*', p);
    // free(p);
    return new;
}

int VarSer_Collection(char *var)
{
    if (getTyp(var) != Collection && getTyp(var) != Set)
    {
        char msg[32];
        sprintf(msg, "%s not defined as a collection", var);
        yyerror(msg);
    }
    return 1;
}

int VarExist(char *var)
{
    if (getTyp(var) == 0)
    {
        return 0;
    }
    return 1;
}

void declaration(char *identifier_list, varType type)
{
    switch (type)
    {
    case Collection:
        printf("set<string> ");
        break;
    case Set:
        printf("set<int> ");
        break;
    case Int:
        printf("int ");
        break;
    case String:
        printf("string ");
        break;
    default:
        break;
    }
    char *temp = malloc(strlen(identifier_list) + 1);
    strcpy(temp, identifier_list);
    char *token;
    token = strtok(temp, "@");
    int comma = 0;
    while (token)
    {
        if (strcmp(token, ""))
        {

            if (VarExist(token))
            {
                char msg[32];
                sprintf(msg, "%s already defined", token);
                yyerror(msg);
            }
            if (comma)
            {
                printf(", ");
            }
            switch (type)
            {
            case Collection:
                insert(token, Collection);
                printf("%s", token);
                comma = 1;
                break;
            case Set:
                insert(token, Set);
                printf("%s", token);
                comma = 1;
                break;
            case Int:
                insert(token, Int);
                printf("%s", token);
                comma = 1;
                break;
            case String:
                insert(token, String);
                printf("%s", token);
                comma = 1;
                break;
            default:
                break;
            }
        }
        token = strtok(NULL, "@");
    }
    free(temp);
    printf(";\n");
}

char *copy_string_without_quotes(const char *input)
{
    size_t len = strlen(input);

    if (len < 2 || input[0] != '"' || input[len - 1] != '"')
    {
        char *result = (char *)malloc(1);
        if (result == NULL)
        {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }
        result[0] = '\0';
        return result;
    }

    char *result = (char *)malloc(len - 1);
    if (result == NULL)
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    strncpy(result, input + 1, len - 2);
    result[len - 2] = '\0';

    return result;
}

char *concate_and_free(char *first, char *second, int free_1, int free_2)
{
    size_t len1 = strlen(first);
    size_t len2 = strlen(second);
    char *result = (char *)malloc(len1 + len2 + 1);
    if (result == NULL)
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    strcpy(result, first);
    strcat(result, second);
    if (free_1 == 1)
        free(first);
    if (free_2 == 1)
        free(second);
    return result;
}

ops_with_type *create_ops_with_type_identifier(char *value)
{
    ops_with_type *new_ops_with_type = (ops_with_type *)malloc(sizeof(ops_with_type));
    if (new_ops_with_type == NULL)
    {
        char msg[32];
        sprintf(msg, "Failed to allocate memory for new ops_with_type\n");
        yyerror(msg);
    }

    new_ops_with_type->value = strdup(value);
    new_ops_with_type->type = getTyp(value);
    if (new_ops_with_type->type == 0)
    {
        char msg[32];
        sprintf(msg, "%s not defined", value);
        yyerror(msg);
    }
    free(value);
    return new_ops_with_type;
}

void assignment_op(char *identifier, ops_with_type *operation)
{
    if (operation->type != getTyp(identifier))
    {
        char msg[32];
        sprintf(msg, "Type mismatch in assignment of %s", identifier);
        yyerror(msg);
    }
    printf("%s = %s;\n", identifier, operation->value);
    free(operation->value);
    free(operation);
}

ops_with_type *create_ops_with_type_literal(literal_with_type *literal)
{
    ops_with_type *new_ops_with_type = (ops_with_type *)malloc(sizeof(ops_with_type));
    if (new_ops_with_type == NULL)
    {
        char msg[32];
        sprintf(msg, "Failed to allocate memory for new ops_with_type\n");
        yyerror(msg);
    }
    new_ops_with_type->type = literal->type;
    switch (literal->type)
    {
    case Collection:
        new_ops_with_type->value = malloc(39);
        strcpy(new_ops_with_type->value, "(make_literal");
        break;
    case Set:
        new_ops_with_type->value = malloc(36);
        strcpy(new_ops_with_type->value, "(make_literal");
        break;
    case Int:
        new_ops_with_type->value = malloc(31);
        strcpy(new_ops_with_type->value, "(make_literal");
        break;
    case String:
        new_ops_with_type->value = malloc(34);
        strcpy(new_ops_with_type->value, "(make_literal");
        break;
    default:
        break;
    }
    char *temp;
    char *token;
    char *comma;
    switch (literal->type)
    {
    case Collection:
        new_ops_with_type->value = concate_and_free(new_ops_with_type->value, "<string>({", 1, 0);
        if (literal->value[0] == '\0')
        {
            new_ops_with_type->value = concate_and_free(new_ops_with_type->value, "}))", 1, 0);
        }
        else
        {
            temp = malloc(strlen(literal->value) + 1);
            strcpy(temp, literal->value);
            token = strtok(temp, "@");
            comma = "";
            do
            {
                if (token)
                {
                    new_ops_with_type->value = concate_and_free(new_ops_with_type->value, comma, 1, 0);
                    new_ops_with_type->value = concate_and_free(new_ops_with_type->value, "\"", 1, 0);
                    new_ops_with_type->value = concate_and_free(new_ops_with_type->value, token, 1, 0);
                    new_ops_with_type->value = concate_and_free(new_ops_with_type->value, "\"", 1, 0);
                }
                comma = ", ";
                token = strtok(NULL, "@");
            } while (token);
            free(temp);
            new_ops_with_type->value = concate_and_free(new_ops_with_type->value, "}))", 1, 0);
        }
        break;
    case Set:
        new_ops_with_type->value = concate_and_free(new_ops_with_type->value, "<int>({", 1, 0);
        if (literal->value[0] == '\0')
        {
            new_ops_with_type->value = concate_and_free(new_ops_with_type->value, "}))", 1, 0);
        }
        else
        {
            temp = malloc(strlen(literal->value) + 1);
            strcpy(temp, literal->value);
            token = strtok(temp, "@");
            comma = "\0";
            do
            {
                if (token)
                {
                    new_ops_with_type->value = concate_and_free(new_ops_with_type->value, comma, 1, 0);
                    new_ops_with_type->value = concate_and_free(new_ops_with_type->value, token, 1, 0);
                }
                comma = ", ";
                token = strtok(NULL, "@");
            } while (token);
            free(temp);
            new_ops_with_type->value = concate_and_free(new_ops_with_type->value, "}))", 1, 0);
        }
        break;
    case Int:
        new_ops_with_type->value = concate_and_free(new_ops_with_type->value, "(", 1, 0);
        new_ops_with_type->value = concate_and_free(new_ops_with_type->value, literal->value, 1, 0);
        new_ops_with_type->value = concate_and_free(new_ops_with_type->value, "))", 1, 0);

        break;
    case String:
        new_ops_with_type->value = concate_and_free(new_ops_with_type->value, "(\"", 1, 0);
        new_ops_with_type->value = concate_and_free(new_ops_with_type->value, literal->value, 1, 0);
        new_ops_with_type->value = concate_and_free(new_ops_with_type->value, "\"))", 1, 0);
        break;
    default:
        break;
    }
    free(literal->value);
    free(literal);
    return new_ops_with_type;
}

ops_with_type *operation_with_command(ops_with_type *first, char op, ops_with_type *seccond)
{
    char *new_op = malloc(4);
    strcpy(new_op, " \0");
    switch (op)
    {
    case '+':
        if (first->type == String && seccond->type == String)
        {
            char msg[32];
            sprintf(msg, "cant do + between Strings\n");
            yyerror(msg);
        }
        new_op = concate_and_free(new_op, "+ ", 1, 0);
        break;
    case '-':
        if (first->type == String && seccond->type == String)
        {
            char msg[32];
            sprintf(msg, "cant do - between Strings\n");
            yyerror(msg);
        }
        new_op = concate_and_free(new_op, "- ", 1, 0);
        break;
    case '*':
        if (first->type == Set && seccond->type == Set)
        {
            char msg[32];
            sprintf(msg, "cant do * between Set\n");
            yyerror(msg);
        }
        if (first->type == Collection && seccond->type == Collection)
        {
            char msg[32];
            sprintf(msg, "cant do * between Collection\n");
            yyerror(msg);
        }
        if (first->type == String && seccond->type == String)
        {
            char msg[32];
            sprintf(msg, "cant do * between String\n");
            yyerror(msg);
        }
        new_op = concate_and_free(new_op, "* ", 1, 0);
        break;
    case '/':
        if (first->type == Collection && seccond->type == Collection)
        {
            char msg[32];
            sprintf(msg, "cant do / between Collection\n");
            yyerror(msg);
        }
        if (first->type == Set && seccond->type == Set)
        {
            char msg[32];
            sprintf(msg, "cant do / between Set\n");
            yyerror(msg);
        }
        if (first->type == String && seccond->type == String)
        {
            char msg[32];
            sprintf(msg, "cant do / between String\n");
            yyerror(msg);
        }
        new_op = concate_and_free(new_op, "/ ", 1, 0);
        break;
    case '&':
        if (first->type == String && seccond->type == String)
        {
            char msg[32];
            sprintf(msg, "cant do & between String\n");
            yyerror(msg);
        }
        if (first->type == Int && seccond->type == Int)
        {
            char msg[32];
            sprintf(msg, "cant do & between Int\n");
            yyerror(msg);
        }
        new_op = concate_and_free(new_op, "* ", 1, 0);
        break;
    default:
        break;
    }
    ops_with_type *new_ops_with_type = (ops_with_type *)malloc(sizeof(ops_with_type));
    if (new_ops_with_type == NULL)
    {
        char msg[32];
        sprintf(msg, "Failed to allocate memory for new ops_with_type\n");
        yyerror(msg);
    }
    if ((first->type != seccond->type) && ((first->type + seccond->type) != 5))
    {
        char msg[32];
        sprintf(msg, "Type mismatch in operation");
        yyerror(msg);
    }
    if (((first->type == String) && (seccond->type == Collection)) || ((first->type == Collection) && (seccond->type == String)))
    {
        new_ops_with_type->type = Collection;
        if (first->type == String) // change the first to collection
        {
            first->value = concate_and_free("(make_literal<string>({", first->value, 0, 1);
            first->value = concate_and_free(first->value, "}))", 1, 0);
        }
        else // change the seccond to collection
        {
            seccond->value = concate_and_free("(make_literal<string>({", seccond->value, 0, 1);
            seccond->value = concate_and_free(seccond->value, "}))", 1, 0);
        }
    }
    else if (((first->type == Set) && (seccond->type == Int)) || ((first->type == Int) && (seccond->type == Set)))
    {
        new_ops_with_type->type = Set;
        if (first->type == Int) // change the first to Set
        {
            first->value = concate_and_free("(make_literal<int>({", first->value, 0, 1);
            first->value = concate_and_free(first->value, "}))", 1, 0);
        }
        else // change the seccond to Set
        {
            seccond->value = concate_and_free("(make_literal<int>({", seccond->value, 0, 1);
            seccond->value = concate_and_free(seccond->value, "}))", 1, 0);
        }
    }
    else
    {
        new_ops_with_type->type = first->type;
    }

    new_ops_with_type->value = malloc(2);
    strcpy(new_ops_with_type->value, "\0");
    new_ops_with_type->value = concate_and_free(new_ops_with_type->value, first->value, 1, 0);
    new_ops_with_type->value = concate_and_free(new_ops_with_type->value, new_op, 1, 0);
    new_ops_with_type->value = concate_and_free(new_ops_with_type->value, seccond->value, 1, 0);
    return new_ops_with_type;
}

ops_with_type *add_bracets_to_op(ops_with_type *operation)
{
    operation->value = concate_and_free("( ", operation->value, 0, 1);
    operation->value = concate_and_free(operation->value, " )", 1, 0);
    return operation;
}

ops_with_type *size_set_or_collection(ops_with_type *operation)
{
    if (operation->type != Collection && operation->type != Set)
    {
        char msg[32];
        sprintf(msg, "cant do size | | on non collection or set\n");
        yyerror(msg);
    }
    ops_with_type *new_ops_with_type = (ops_with_type *)malloc(sizeof(ops_with_type));
    if (new_ops_with_type == NULL)
    {
        char msg[32];
        sprintf(msg, "Failed to allocate memory for new ops_with_type\n");
        yyerror(msg);
    }
    new_ops_with_type->type = Int;
    new_ops_with_type->value = malloc(2);
    strcpy(new_ops_with_type->value, "\0");
    new_ops_with_type->value = concate_and_free(new_ops_with_type->value, "(", 1, 0);
    new_ops_with_type->value = concate_and_free(new_ops_with_type->value, operation->value, 1, 2);
    new_ops_with_type->value = concate_and_free(new_ops_with_type->value, ").size()", 1, 0);
    return new_ops_with_type;
}

ops_with_type *condition_op(ops_with_type *first, char *op, ops_with_type *seccond)
{
    if (first->type != seccond->type)
    {
        char msg[32];
        sprintf(msg, "Type mismatch in condition");
        yyerror(msg);
    }
    if (first->type == Collection || first->type == Set)
    {
        if (strcmp(op, "==") != 0)
        {
            char msg[32];
            sprintf(msg, "cant do condition on Collection or Set");
            yyerror(msg);
        }
    }
    ops_with_type *new_ops_with_type = (ops_with_type *)malloc(sizeof(ops_with_type));
    if (new_ops_with_type == NULL)
    {
        char msg[32];
        sprintf(msg, "Failed to allocate memory for new ops_with_type\n");
        yyerror(msg);
    }
    new_ops_with_type->type = first->type;
    new_ops_with_type->value = malloc(2);
    strcpy(new_ops_with_type->value, "\0");
    new_ops_with_type->value = concate_and_free(new_ops_with_type->value, first->value, 1, 0);
    new_ops_with_type->value = concate_and_free(new_ops_with_type->value, " ", 1, 0);
    new_ops_with_type->value = concate_and_free(new_ops_with_type->value, op, 1, 0);
    new_ops_with_type->value = concate_and_free(new_ops_with_type->value, " ", 1, 0);
    new_ops_with_type->value = concate_and_free(new_ops_with_type->value, seccond->value, 1, 0);
    return new_ops_with_type;
}

ops_with_type *not_condition_op(ops_with_type *first)
{
    ops_with_type *new_ops_with_type = (ops_with_type *)malloc(sizeof(ops_with_type));
    if (new_ops_with_type == NULL)
    {
        char msg[32];
        sprintf(msg, "Failed to allocate memory for new ops_with_type\n");
        yyerror(msg);
    }
    new_ops_with_type->type = first->type;
    new_ops_with_type->value = malloc(2);
    strcpy(new_ops_with_type->value, "\0");
    new_ops_with_type->value = concate_and_free(new_ops_with_type->value, "!( ", 1, 0);
    new_ops_with_type->value = concate_and_free(new_ops_with_type->value, first->value, 1, 0);
    new_ops_with_type->value = concate_and_free(new_ops_with_type->value, " )", 1, 0);
    return new_ops_with_type;
}

void for_loop(char *identifier_runner, char *identifier_base)
{
    if ((getTyp(identifier_runner) != Int && getTyp(identifier_base) != Set) && (getTyp(identifier_runner) != String && getTyp(identifier_base) != Collection))
    {
        char msg[32];
        sprintf(msg, "for loop must be on 'int : set' or 'string : collection'\n");
        yyerror(msg);
    }
    switch (getTyp(identifier_runner))
    {
        case Int:
            printf("for(const int& %s : %s)\n", identifier_runner, identifier_base);
            break;
            case String:
            printf("for(const string& %s : %s)\n", identifier_runner, identifier_base);
            break;
    }
}
    // insert to main YACC


