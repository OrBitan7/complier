#ifndef MY_collection_H
#define MY_collection_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symTab.h"

extern char *yytext;


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





char *CopyStr(char *str);
char *AddStrToList(char *list, char *str);
char *AddToList(char *list, char *str);

void insert(char *varName, varType typ);
varType getTyp(char *var);

void GenerateOut(char *str, char *element);

char *CopyINT(char *str);
int VarSer_Collection(char *var);
int VarExist(char *var);


void declaration(char *identifier_list, varType type);
char *copy_string_without_quotes(const char *input);
char * concate_and_free(char *first, char *second,int free_1,int free_2);
ops_with_type *create_ops_with_type_identifier(char *value);
void assignment_op(char *identifier, ops_with_type *operation);
ops_with_type *create_ops_with_type_literal(literal_with_type *literal);
ops_with_type *operation_with_command(ops_with_type *first, char op, ops_with_type *seccond);
ops_with_type * add_bracets_to_op(ops_with_type *operation);
ops_with_type * size_set_or_collection(ops_with_type* operation);
ops_with_type * condition_op(ops_with_type * first,char * op,ops_with_type * seccond);
ops_with_type * not_condition_op(ops_with_type * first);
void for_loop(char * identifier_runner,char * identifier_base);




void yyerror(char *s);
int yylex();

#endif // MY_HEADER_H
