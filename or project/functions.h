#ifndef MY_collection_H
#define MY_collection_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symTab.h"

extern char *yytext;

typedef enum
{
    identifier = 1,
} ops_tag;

typedef struct ops_node
{
    char *op;
    struct ops_node *next;

} ops;
typedef struct ops_link_list
{
    ops_tag typ;
    char *op;
    ops *head;
    ops *tail;

} ops_link_list;

typedef struct literal_with_type
{
    char *value;
    varType type;
} literal_with_type;

typedef struct ops_with_type
{
    char *value;
    varType type;
} ops_with_type;



extern int size;
extern ops_link_list** global_ops_lists;

//link list op functions:
void add_new_ops_link_list(ops_tag tag, char *operation);
void add_node_to_last_ops_list_tail(char *operation);
void add_node_to_last_ops_list_head(char *operation);


char *CopyStr(char *str);
char *AddStrToList(char *list, char *str);
char *AddToList(char *list, char *str);

void insert(char *varName, varType typ);
varType getTyp(char *var);

void GenerateDef(varType type, char *Vars);
// char *GenerateColAssign(char *input);
void GenerateOut(char *str, char *element);

char *concatenate_strings(const char *first, char middle, const char *last);
char *CopyINT(char *str);
// char *GenerateSetAssign(char *input);
int VarSer_Collection(char *var);
int VarExist(char *var);
// void GenerateSetOut(char *str, char *set);


void declaration(char *identifier_list, varType type);
char *copy_string_without_quotes(const char *input);
char * concate_and_free(char *first, char *second,int free_1,int free_2);
ops_with_type *create_ops_with_type_identifier(char *value);
void assignment_op(char *identifier, ops_with_type *operation);
ops_with_type *create_ops_with_type_literal(literal_with_type *literal);


void yyerror(char *s);
int yylex();

#endif // MY_HEADER_H
