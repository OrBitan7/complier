#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <set>
using namespace std;

void yyerror(char *s)
{
	fprintf(stderr, "%s\n", s);
	exit(1);
}


set<string> addStringToCollection(set<string> collection, string str)
{
	collection.insert(str);
	return collection;
}

int main()
{
}