#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void yyerror(char *s)
{
	fprintf(stderr, "%s\n", s);
	exit(1);
}

char *RT_addStrToCollection(char *collection, char *str)
{
	int lenStr = strlen(str);
	int lenColl = 0;
	if (collection == NULL)
	{
		collection = malloc(lenStr + 2);
		strcpy(collection, "\"");
	}
	else
	{
		collection = realloc(collection, strlen(collection) + lenStr + 2);
		strcat(collection, "@");
	}
	strcat(collection, str);
	printf("col:%s\n", collection);
	printf("str:%s\n", str);
	return collection;
}

char *RT_RemoveStrToCollection(char *collection, char *str)
{

	if (collection == NULL || str == NULL)
	{
		return collection;
	}

	char *pos = strstr(collection, str);
	if (pos != NULL)
	{
		// printf("pos:%s\n", pos);
		// printf("str:%s\n", str);
		// printf("next:%c\n", pos[strlen(str)]);
		// printf("beffor:%c\n", pos[-1]);
		int lenStr = strlen(str);
		int lenColl = strlen(collection);
		int lenRemain = lenColl - lenStr;
		// fprintf(stdout, "itration\n");
		if (pos[strlen(str)] == '@')
		{
			// printf("1\n");
			lenStr++;
			memmove(pos, pos + lenStr, strlen(pos + lenStr) + 1);
			// printf("new_pos:%s\n", pos);
		}
		else if (pos[-1] == '@')
		{
			lenStr++;
			pos--;
			memmove(pos, pos + lenStr, strlen(pos + lenStr) + 1);
			// printf("2\n");
			// printf("new_pos:%s\n", pos);
		}
		else
		{
			memmove(pos, pos + lenStr, strlen(pos + lenStr) + 1);
			// printf("3\n");
			// printf("new_pos:%s\n", pos);
		}

		collection = realloc(collection, lenRemain + 1);
	}

	return collection;
}

char *RT_unifyCollections(char *var, char *coll)
{
	char *temp = malloc(strlen(coll) + 1);
	strcpy(temp, coll);
	char *token;
	token = strtok(temp + 1, "@");
	do
	{
		// printf("token:%s\n", token);
		if (token && (strstr(var, token) == NULL))
		{
			var = RT_addStrToCollection(var, token);
			// printf("var in itration:%s\n", var);
		}
		token = strtok(NULL, "@");
	} while (token);
	free(temp);
	// printf("var:%s\n", var);
	// printf("var_len:%d\n", strlen(var));
	return var;
}
char *RT_DifferenceCollections(char *var, char *coll)
{
	char *temp = malloc(strlen(coll) + 1);
	strcpy(temp, coll);
	char *token;
	token = strtok(temp + 1, "@");
	do
	{
		if (token && (strstr(var, token) != NULL))
		{
			var = RT_RemoveStrToCollection(var, token);
			// printf("var in itration:%s\n", var);
		}
		token = strtok(NULL, "@");
	} while (token);
	free(temp);
	return var;
}
int main()
{
	char *a = NULL;
	char *b = NULL;
	{
		int len;
		len = strlen("\"hello@lla@hi");
		if (a == NULL)
			a = malloc(len + 1);
		else
			a = realloc(a, len + 1);
		strcpy(a, "\"hello@lla@hi");
	}
	{
		int len;
		len = strlen("\"lol");
		if (b == NULL)
			b = malloc(len + 1);
		else
			b = realloc(b, len + 1);
		strcpy(b, "\"lol");
	}
	printf("a before =%s\n", a); /////////////////////

	// {
	// 	char *unified = RT_DifferenceCollections(a, b);
	// 	int len = strlen(unified);
	// 	if (a == NULL)
	// 		a = malloc(len + 1);
	// 	else
	// 		a = realloc(a, len + 1);
	// 	strcpy(a, unified);
	// }
	{
		char *unified = RT_unifyCollections(a, b);
		int len = strlen(unified);
		printf("%d,%d\n", a, unified);
		printf("\nunified:%s\n", unified);
		printf("l_len:%d\n", strlen(a));
		printf("a:%s\n", a);
		if (a == NULL)
			a = malloc(len + 1);
		else
			a = realloc(a, strlen(a) + len + 2);
		printf("len:%d\nlen_a:%d\nnew_len:%d\n ", len, strlen(a), strlen(a) + len + 2);
		printf("\a:%s\n", a);
		strcpy(a, unified);
	}
	printf("a after =%s\n", a);
}