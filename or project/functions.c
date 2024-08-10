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

int size = 0;
ops_link_list **global_ops_lists = NULL;

// link list functions  ===========================================

void add_new_ops_link_list(ops_tag tag, char *operation)
{
    size++;
    if (size == 1)
    {
        global_ops_lists = malloc(size * sizeof(ops_link_list *));
    }
    else
    {
        global_ops_lists = realloc(global_ops_lists, size * sizeof(ops_link_list *));
    }
    if (global_ops_lists == NULL)
    {
        char msg[32];
        sprintf(msg, "Failed to allocate memory for global_ops_lists\n");
        yyerror(msg);
    }

    ops_link_list *new_list = (ops_link_list *)malloc(sizeof(ops_link_list));
    if (new_list == NULL)
    {
        char msg[32];
        sprintf(msg, "Failed to allocate memory for global_ops_lists\n");
        yyerror(msg);
    }

    new_list->typ = tag;
    new_list->op = strdup(operation);
    new_list->head = new_list->tail = NULL;

    global_ops_lists[size - 1] = new_list;
}

void add_node_to_last_ops_list_tail(char *operation)
{
    if (size == 0)
    {
        char msg[32];
        sprintf(msg, "No ops_link_list exists in global_ops_lists\n");
        yyerror(msg);
    }

    ops_link_list *last_list = global_ops_lists[size - 1];
    ops *new_node = (ops *)malloc(sizeof(ops));
    if (new_node == NULL)
    {
        char msg[32];
        sprintf(msg, "Failed to allocate memory for new ops_node\n");
        yyerror(msg);
    }

    new_node->op = strdup(operation);
    new_node->next = NULL;

    if (last_list->tail == NULL)
    {
        last_list->head = last_list->tail = new_node;
    }
    else
    {
        last_list->tail->next = new_node;
        last_list->tail = new_node;
    }
}

void add_node_to_last_ops_list_head(char *operation)
{
    if (size == 0)
    {
        char msg[32];
        sprintf(msg, "No ops_link_list exists in global_ops_lists\n");
        yyerror(msg);
    }

    ops_link_list *last_list = global_ops_lists[size - 1];
    ops *new_node = (ops *)malloc(sizeof(ops));
    if (new_node == NULL)
    {
        char msg[32];
        sprintf(msg, "Failed to allocate memory for new ops_node\n");
        yyerror(msg);
    }

    new_node->op = strdup(operation);
    new_node->next = last_list->head;
    last_list->head = new_node;

    if (last_list->tail == NULL)
    {
        last_list->tail = new_node;
    }
}
void free_global_ops_lists()
{
    for (int i = 0; i < size; i++)
    {
        ops_link_list *list = global_ops_lists[i];
        ops *current = list->head;
        ops *next_node;

        while (current != NULL)
        {
            next_node = current->next;
            free(current->op);
            free(current);
            current = next_node;
        }

        free(list->op);
        free(list);
    }

    free(global_ops_lists);
    global_ops_lists = NULL;
    size = 0;
}

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
// char *GenerateColAssign(char *input)
// {
//     char msg[32];
//     char *result;
//     if ((input[0] != '\"') && getTyp(input) != Collection)
//     {
//         sprintf(msg, "%s not defined as a collection", input);
//         yyerror(msg);
//     }

//     if (input[0] == '\"')
//     {
//         result = malloc(18);
//         strcpy(result, "make_collection({");
//         if (input[strlen(input) - 1] == '\"')
//         {
//             result = (char *)realloc(result, (strlen(result) + 2) * sizeof(char));
//             strcat(result, "})");
//         }
//         else
//         {

//             char *temp = malloc(strlen(input) + 1);
//             strcpy(temp, input);
//             char *token;
//             token = strtok(temp + 1, "@");
//             char *comma = "\0";
//             int i = 1;
//             do
//             {
//                 if (token)
//                 {
//                     result = (char *)realloc(result, (strlen(result) + 3 + strlen(token) + strlen(comma)) * sizeof(char));
//                     if (i != 1)
//                     {
//                         strcat(result, comma);
//                     }
//                     strcat(result, "\"");
//                     strcat(result, token);
//                     strcat(result, "\"");
//                     i = 2;
//                 }
//                 comma = ",";
//                 token = strtok(NULL, "@");
//             } while (token);
//             free(temp);
//             result = (char *)realloc(result, (strlen(result) + 2) * sizeof(char));
//             strcat(result, "})");
//         }
//     }
//     else
//     {
//         result = strdup(input);
//     }
//     return result;
// }
// print collection:
void GenerateOut(char *str, char *element)
{
    printf("printSetWithMessage(%s, \"%s\");\n", element, str);
}

char *concatenate_strings(const char *first, char middle, const char *last)
{

    size_t length = 1;
    if (first)
        length += strlen(first);
    if (last)
        length += strlen(last);
    char *result = (char *)malloc(length + 1);
    if (!result)
        return NULL;

    result[0] = '\0';

    if (first)
        strcat(result, first);

    int temp = strlen(result);
    result[temp] = middle;
    result[temp + 1] = '\0';

    if (last)
        strcat(result, last);

    result[strlen(result)] = '\0';

    return result;
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

// char *GenerateSetAssign(char *input)
// {
//     // printf("input in GenerateSetAssign: %s\n", input);
//     char msg[32];
//     char *result;
//     if ((input[0] != '*') && getTyp(input) != Set && VarExist(input) == 0)
//     {
//         sprintf(msg, "%s not defined as a Set", input);
//         yyerror(msg);
//     }

//     if (input[0] == '*')
//     {
//         result = malloc(11);
//         strcpy(result, "make_Set({");
//         if (input[strlen(input) - 1] == '\"')
//         {
//             result = (char *)realloc(result, (strlen(result) + 2) * sizeof(char));
//             strcat(result, "})");
//         }
//         else
//         {
//             char *temp = malloc(strlen(input) + 1);
//             strcpy(temp, input);
//             char *token;
//             token = strtok(temp + 1, "@");
//             char *comma = "\0";
//             int i = 1;
//             do
//             {
//                 if (token)
//                 {
//                     result = (char *)realloc(result, (strlen(result) + 1 + strlen(token) + strlen(comma)) * sizeof(char));
//                     if (i != 1)
//                     {
//                         strcat(result, comma);
//                     }
//                     strcat(result, token);
//                     i = 2;
//                 }
//                 comma = ",";
//                 token = strtok(NULL, "@");
//             } while (token);
//             free(temp);
//             result = (char *)realloc(result, (strlen(result) + 2) * sizeof(char));
//             strcat(result, "})");
//         }
//     }
//     else
//     {
//         result = strdup(input);
//     }
//     // printf("finished GenerateSetAssign result: %s\n", result);
//     return result;
// }

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
// void GenerateSetOut(char *str, char *set)
// {
//     char msg[32];
//     // printf("in GenerateSetOut\n");
//     if ((set[0] != '\"') && getTyp(set) != Set)
//     {
//         sprintf(msg, "%s not defined as a set", set);
//         yyerror(msg);
//     }
//     printf("{ \n");
//     fprintf(stdout, "   cout << \"%s\";\n", str); // Command to print 1st string

//     fprintf(stdout, "   cout << \"[\";\n"); // Command to start set

//     if (set[0] == '*')
//     {
//         char *temp = malloc(strlen(set) + 1);
//         strcpy(temp, set);
//         char *token;
//         token = strtok(temp + 1, "@");
//         char *comma = "";
//         do
//         {
//             if (token)
//                 fprintf(stdout, "   cout << %s%s ;\n", comma, token);
//             comma = ", ";
//             token = strtok(NULL, "@");
//         } while (token);
//         free(temp);
//     }
//     else
//     {
//         fprintf(stdout, "   bool first = true;\n");
//         fprintf(stdout, "   for (const auto& item : %s) {\n", set);
//         fprintf(stdout, "       if (!first) {\n");
//         fprintf(stdout, "           cout << ,;\n");
//         fprintf(stdout, "       }\n");
//         fprintf(stdout, "      cout << item;\n");
//         fprintf(stdout, "      first = false;\n");
//         fprintf(stdout, "   }\n");
//     }

//     fprintf(stdout, "   cout << \"]\" << endl;\n"); // Command to end collection
//     printf("}\n");
// }

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
    new_ops_with_type->value = malloc(15);
    strcpy(new_ops_with_type->value, "(make_literal");
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
