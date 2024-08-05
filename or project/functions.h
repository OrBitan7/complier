#ifndef MY_collection_H
#define MY_collection_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symTab.h"

// משתנים חיצוניים
extern char *yytext;




char *CopyStr(char *str);
char *AddStrToList(char *list, char *str);
char *AddToList(char *list, char *str);

void insert(char *varName, varType typ);
varType getTyp(char *var);

void GenerateDef(varType type, char *Vars);
char *GenerateColAssign(char *input);
void GenerateColOut(char *str, char *coll);
void GenerateColUnion(char *varResultName, char *varName, char *coll);
void GenerateColUnionWithString(char *varResultName, char *varName, char *string);
void GenerateColDifference(char *varResultName, char *varName, char *coll);
void GenerateColDifferenceWithString(char *varResultName, char *varName, char *remove_strint);

void CollectionPlusCollection(char *varName, char *remove_strint);
char *concatenate_strings(const char* first, char middle, const char* last);



void yyerror(char *s);
int yylex();

#endif // MY_HEADER_H
