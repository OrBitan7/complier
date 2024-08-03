#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>
#include <set>

using namespace std;

void yyerror(char *s)
{
	fprintf(stderr, "%s\n", s);
	exit(1);
}

// char *RT_addStrToCollection(char *collection, char *str)
// {
// 	int lenStr = strlen(str);
// 	int lenColl = 0;
// 	if (collection == NULL)
// 	{
// 		collection = malloc(lenStr + 2);
// 		strcpy(collection, "\"");
// 	}
// 	else
// 	{
// 		collection = realloc(collection, strlen(collection) + lenStr + 1);
// 		strcat(collection, "@");
// 	}
// 	strcat(collection, str);
// 	return collection;
// }

// char *RT_unifyCollections(char *var, char *coll)
// {
// 	char *temp = malloc(strlen(coll) + 1);
// 	strcpy(temp, coll);
// 	char *token;
// 	token = strtok(temp + 1, "@");
// 	do
// 	{
// 		if (token && (strstr(var, token) == NULL))
// 			var = RT_addStrToCollection(var, token);
// 		token = strtok(NULL, "@");
// 	} while (token);
// 	free(temp);

// 	return var;
// }

int main()
{
	// collection a;
	set<string> a;
	// a = {"hi", "lol"};
	{
		a.insert("hi");
		a.insert("lol");
	}
	// collection b;
	set<string> b;
	// b = {"hello"};
	{
		b.insert("hello");
	}
	// output "a: " a;
	{
		cout << "a: ";
		cout << "{";
		bool first = true;
		for (const auto &item : a)
		{
			if (!first)
			{
				cout << ", ";
			}
			cout << item;
			first = false;
		}
		cout << "}" << endl;
	}
	// output "new one: " {"or","laodsae"} ;
	{
		cout << "new one: ";
		cout << "{";
		cout << "or";
		cout << ", laodsae";
		cout << "}" << endl;
	}
}
