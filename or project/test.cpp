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
		b.insert("hi");
	}

	//	collection c;
	set<string> c;

	//	c = a + b ;
	{
		c.insert(a.begin(), a.end());
		c.insert(b.begin(), b.end());
	}

	//  collection d;
	set<string> d;

	//	d = b + {"workinggg","yessss"} ;
	{
		d.insert(b.begin(), b.end());
		d.insert("workinggg");
		d.insert("yessss");
		d.insert("yessss");
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
		// output "b: " b;
	{
		cout << "b: ";
		cout << "{";
		bool first = true;
		for (const auto &item : b)
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
	// output "c: " c;
	{
		cout << "c: ";
		cout << "{";
		bool first = true;
		for (const auto &item : c)
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
	// output "d: " d;
	{
		cout << "d: ";
		cout << "{";
		bool first = true;
		for (const auto &item : d)
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
}
