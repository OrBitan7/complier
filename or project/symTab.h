#ifndef MY_symboltab_H
#define MY_symboltab_H

typedef enum {Collection=1, Set=2, Int=3, String=4} varType;

struct {
	char *name;
	varType typ;
} SymTable[100];
#endif