%{
void yyerror (char *s);
int yylex();
#include <stdio.h>     
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "symTab.h"
#include "functions.h"
extern char* yytext;
extern int size;

FILE *outputFile, *inputFile;

//	===	YACC Helper Functions	============================

char* CopyStr(char* str)
{
    char *new, *p;

    if (str[0] == '\"') {           
        new = malloc(strlen(str));
        if ((p = strchr(str+1, '\"')))
            *p = '\0';
        strcpy(new, str);
    }
    else {
        new = malloc(strlen(str)+1);   
        strcpy(new, str);
    }

    return new;
}

char* AddStrToList(char* list, char* str)
{
    char *p;
    char *new = realloc(list, strlen(list)+strlen(str));
    strcat(new, "@");
    if ((p = strchr(str+1, '\"')))
        *p = '\0';
    strcat(new, str+1);
	return new;
}
char *AddToList(char *list, char *str)
{
    char *new = realloc(list, strlen(list) + strlen(str)+2);
    strcat(new, "@");
    strcat(new, str);
    return new;
}
static int idx=0;

void insert(char* varName, varType typ)
{	
    for (int i = 0; i < idx; i++)
    {
        if (strcmp(SymTable[i].name, varName) == 0)
        {
            yyerror("Variable already defined\n");
            return;
        }
    }
	SymTable[idx].name = malloc(strlen(varName)+1);
	strcpy(SymTable[idx].name, varName);
    SymTable[idx].typ = typ;
	++idx;
}

varType getTyp(char* var)
{
    for (int i=0 ; i<idx ; ++i)
        if (strcmp(SymTable[i].name, var)==0)
            return SymTable[i].typ;
    return 0;
}



%}

%union {
        struct literal_with_type* literal_struct;
        struct ops_with_type* ops_struct;
        char *str;
        int number;
        }         /* Yacc definitions */
%token <str> t_STRING t_ID t_INT
%token t_IF_CMD t_ELSE_CMD t_FOR_CMD t_WHILE_CMD t_BIGGER_EQUAL t_LOWER_EQUAL t_EQUAL t_NOT t_COLLECTION_CMD t_SET_CMD t_INT_CMD t_STRING_CMD t_INPUT_CMD t_OUTPUT_CMD t_LOWER t_BIGGER  
%type <str> STRING_LIST INT_LIST identifier identifier_list number_literal string_literal
%type <str> set_literal collection_literal String_
%type <literal_struct> literal
%type <ops_struct> expression operation condition




%%



prog :
                    prog statement                          {}
    |				statement                               {}
    ;
statement:
                    declaration                             {}
    |               assignment                              {}
    |               operation_statement                     {}
    |               control                                 {}
    |               io                                      {}
    |               block                                   {}
    |               else_                                   {}
    ;                                                
declaration :       t_INT_CMD identifier_list ';'           {declaration($2, Int);}
    |               t_STRING_CMD identifier_list ';'        {declaration($2, String);}
    |               t_SET_CMD identifier_list ';'           {declaration($2, Set);}
    |               t_COLLECTION_CMD identifier_list ';'    {declaration($2, Collection);}
    ;
assignment:
                    identifier '=' operation ';'            {assignment_op($1, $3);}
    ;
operation_statement:
                    operation ';'                           {printf("%s;\n", $1->value);}
    ;
operation:
                    operation '+' expression                 {$$ = operation_with_command($1,'+',$3);}
    |               operation '-' expression                 {$$ = operation_with_command($1,'-',$3);}
    |               operation '*' expression                 {$$ = operation_with_command($1,'*',$3);}
    |               operation '/' expression                 {$$ = operation_with_command($1,'/',$3);}
    |               operation '&' expression                 {$$ = operation_with_command($1,'&',$3);} //collection and set onlly
    |               '|' operation '|'                        {$$ = size_set_or_collection($2);}        //collection and set onlly
    |               expression                               {$$ = $1;}
    ;
expression:
                    literal                                  {$$ = create_ops_with_type_literal($1);}
    |               identifier                               {$$ = create_ops_with_type_identifier($1);}
    |              '(' operation ')'                         {$$ = add_bracets_to_op($2);}
    ;       
control:        
                    t_IF_CMD '(' condition ')'{printf("if(%s)\n",$3->value)} statement      {}
    |               t_WHILE_CMD '(' condition ')'{printf("while(%s)\n",$3->value);} statement                     {}
    |               t_FOR_CMD '(' identifier ':' identifier ')' {for_loop($3,$5)} statement       {}
    ;
else_:
                    t_ELSE_CMD {printf("else\n")}statement  {}
    ;
condition:
                    operation t_BIGGER operation            {$$ = condition_op($1, ">", $3);}
    |               operation t_LOWER operation             {$$ = condition_op($1, "<", $3);}
    |               operation t_BIGGER_EQUAL operation      {$$ = condition_op($1, ">=", $3);}
    |               operation t_LOWER_EQUAL operation       {$$ = condition_op($1, "<=", $3);}
    |               operation t_EQUAL operation             {$$ = condition_op($1, "==", $3);}
    |               t_NOT condition                         {$$ = not_condition_op($2);}
    |               '(' condition ')'                       {$$ = add_bracets_to_op($2);}
    |               operation                               {if($1->type == Set || $1->type == Collection) $$ = size_set_or_collection($1); else $$ = $1;}
    ;
io:
                    t_INPUT_CMD String_ identifier ';'      {printf("input_from_user(make_literal(\"%s\"),%s);\n",$2,$3);}
    |               t_OUTPUT_CMD String_  ';'               {printf("printSetWithMessage(\"%s\");\n",$2);}
    |               t_OUTPUT_CMD String_ operation ';'      {GenerateOut($2, $3->value);}
    ;
String_:
                    t_STRING                                {$$ = copy_string_without_quotes(yytext);}
    ;
block:
                    '{'{printf("{\n")} statement_list '}'{printf("}\n")}    {}
    ;
statement_list:
                    statement                               {}
    |               statement_list statement                {}
    ;
identifier:
                    t_ID                                    {$$ = CopyStr(yytext);}
    ;
identifier_list:
                    identifier                              {$$ = $1}
    |               identifier_list ',' identifier          {$$ = AddToList($1, $3); free($3);}
    ;
literal:
                    number_literal                          {$$ = malloc(sizeof(struct literal_with_type)); $$->type = Int; $$->value = $1; }
    |               string_literal                          {$$ = malloc(sizeof(struct literal_with_type)); $$->type = String; $$->value = $1; }
    |               set_literal                             {$$ = malloc(sizeof(struct literal_with_type)); $$->type = Set; $$->value = $1;  }
    |               collection_literal                      {$$ = malloc(sizeof(struct literal_with_type)); $$->type = Collection; $$->value = $1;}
    ;
number_literal:
                    t_INT                                   {$$ = CopyINT(yytext);}
    ;
INT_LIST:
                    t_INT                                   {$$ = CopyINT(yytext);}
    |               INT_LIST ',' t_INT                      {$$ = AddToList($1, yytext);}
    ;
STRING_LIST:
                    t_STRING                                {$$ = copy_string_without_quotes(yytext);}
    |               STRING_LIST ',' t_STRING                {$$ = AddToList($1, copy_string_without_quotes(yytext));}
    ;
string_literal:
                    t_STRING                                {$$ = copy_string_without_quotes(yytext);}
    ;
set_literal:
                    '[' ']'                                 {$$ = CopyINT("\0");}
    |               '[' INT_LIST ']'                        {$$ = $2;}
    ;
collection_literal:
                    '{' '}'                                 {$$ = CopyINT("\0");}
    |               '{' STRING_LIST '}'                     {$$ = $2;}
    ;




%%
extern int yylineno;

void yyerror(char *s) {
    fprintf(stderr, "Error: %s at line %d\n", s, yylineno);
}
int main(void) {


    outputFile = freopen("test.cpp", "w", stdout);
    if (outputFile == NULL) {
        fprintf(stderr, "Error opening output file.\n");
        return 1;
    }

    inputFile = freopen("INPUT.txt", "r", stdin);
    if (inputFile == NULL) {
        fprintf(stderr, "Error opening input file.\n");
        return 1;
    }

    fprintf(stdout, "#include <stdio.h>\n");
    fprintf(stdout, "#include <stdlib.h>\n");
    fprintf(stdout, "#include <string.h>\n");
    fprintf(stdout, "#include <iostream>\n");
    fprintf(stdout, "#include <string>\n");
    fprintf(stdout, "#include <set>\n\n");
    fprintf(stdout, "#include <sstream>\n\n");
    fprintf(stdout, "#include <algorithm>\n\n");
    fprintf(stdout, "#include <initializer_list>\n\n");
    
    fprintf(stdout, "using namespace std;\n\n");

    fprintf(stdout, "template<typename T>\n");
    fprintf(stdout, "set<T> make_literal(initializer_list<T> list) {\n");
    fprintf(stdout, "    return set<T>(list);\n");
    fprintf(stdout, "}\n");

    fprintf(stdout, "//COLLECTION operators\n");
    fprintf(stdout, "set<string> operator-(const set<string>& set1, const set<string>& set2) {\n");
    fprintf(stdout, "    set<string> result = set1;\n");
    fprintf(stdout, "    for (const string& elem : set2) {\n");
    fprintf(stdout, "        result.erase(elem);\n");
    fprintf(stdout, "    }\n");
    fprintf(stdout, "    return result;\n");
    fprintf(stdout, "}\n");
    
    fprintf(stdout, "set<string> operator+(const set<string>& set1, const set<string>& set2) {\n");
    fprintf(stdout, "    set<string> result = set1;\n");
    fprintf(stdout, "    result.insert(set2.begin(), set2.end());\n");
    fprintf(stdout, "    return result;\n");
    fprintf(stdout, "}\n");

    fprintf(stdout, "set<string> operator+(const set<string>& set1, const string& str) {\n");
    fprintf(stdout, "    set<string> result = set1;\n");
    fprintf(stdout, "    result.insert(str);\n");
    fprintf(stdout, "    return result;\n");
    fprintf(stdout, "}\n");

    fprintf(stdout, "set<string> operator*(const set<string>& set1, const set<string>& set2) {\n");
    fprintf(stdout, "    set<string> result;\n");
    fprintf(stdout, "    for (const string& elem : set1) {\n");
    fprintf(stdout, "        if (set2.find(elem) != set2.end()) {\n");
    fprintf(stdout, "            result.insert(elem);\n");
    fprintf(stdout, "        }\n");
    fprintf(stdout, "    }\n");
    fprintf(stdout, "    return result;\n");
    fprintf(stdout, "}\n");

    fprintf(stdout, "void printSetWithMessage(const set<string>& mySet, const string& message) {\n");
    fprintf(stdout, "    cout << message << \" {\";\n");
    fprintf(stdout, "    auto it = mySet.begin();\n");
    fprintf(stdout, "    if (it != mySet.end()) {\n");
    fprintf(stdout, "        cout << \"\\\"\" << *it << \"\\\"\";\n");
    fprintf(stdout, "        ++it;\n");
    fprintf(stdout, "    }\n");
    fprintf(stdout, "    while (it != mySet.end()) {\n");
    fprintf(stdout, "        cout << \", \\\"\" << *it << \"\\\"\";\n");
    fprintf(stdout, "        ++it;\n");
    fprintf(stdout, "    }\n");
    fprintf(stdout, "    cout << \"}\" << endl;\n");
    fprintf(stdout, "}\n");

    fprintf(stdout, "//SET operators\n");
    fprintf(stdout, "set<int> operator-(const set<int>& set1, const set<int>& set2) {\n");
    fprintf(stdout, "    set<int> result = set1;\n");
    fprintf(stdout, "    for (const int& elem : set2) {\n");
    fprintf(stdout, "        result.erase(elem);\n");
    fprintf(stdout, "    }\n");
    fprintf(stdout, "    return result;\n");
    fprintf(stdout, "}\n");
    
    fprintf(stdout, "set<int> operator+(const set<int>& set1, const set<int>& set2) {\n");
    fprintf(stdout, "    set<int> result = set1;\n");
    fprintf(stdout, "    result.insert(set2.begin(), set2.end());\n");
    fprintf(stdout, "    return result;\n");
    fprintf(stdout, "}\n");

    fprintf(stdout, "set<int> operator+(const set<int>& set1, const int& str) {\n");
    fprintf(stdout, "    set<int> result = set1;\n");
    fprintf(stdout, "    result.insert(str);\n");
    fprintf(stdout, "    return result;\n");
    fprintf(stdout, "}\n");

    fprintf(stdout, "set<int> operator*(const set<int>& set1, const set<int>& set2) {\n");
    fprintf(stdout, "    set<int> result;\n");
    fprintf(stdout, "    for (const int& elem : set1) {\n");
    fprintf(stdout, "        if (set2.find(elem) != set2.end()) {\n");
    fprintf(stdout, "            result.insert(elem);\n");
    fprintf(stdout, "        }\n");
    fprintf(stdout, "    }\n");
    fprintf(stdout, "    return result;\n");
    fprintf(stdout, "}\n");

    fprintf(stdout, "void printSetWithMessage(const set<int>& mySet, const string& message) {\n");
    fprintf(stdout, "    cout << message << \" [\";\n");
    fprintf(stdout, "    auto it = mySet.begin();\n");
    fprintf(stdout, "    if (it != mySet.end()) {\n");
    fprintf(stdout, "        cout << *it ;\n");
    fprintf(stdout, "        ++it;\n");
    fprintf(stdout, "    }\n");
    fprintf(stdout, "    while (it != mySet.end()) {\n");
    fprintf(stdout, "        cout << \",\" << *it ;\n");
    fprintf(stdout, "        ++it;\n");
    fprintf(stdout, "    }\n");
    fprintf(stdout, "    cout << \"]\" << endl;\n");
    fprintf(stdout, "}\n");

    fprintf(stdout, "//INT operators\n");
    fprintf(stdout, "int make_literal(int list) {\n");
    fprintf(stdout, "    return list;\n");
    fprintf(stdout, "}\n");

    fprintf(stdout, "void printSetWithMessage(const int& myINT, const string& message) {\n");
    fprintf(stdout, "    cout << message << \" \" << myINT << endl;\n");
    fprintf(stdout, "}\n");

    fprintf(stdout, "//STRING operators\n");
    fprintf(stdout, "string make_literal(string list) {\n");
    fprintf(stdout, "    return list;\n");
    fprintf(stdout, "}\n");

    fprintf(stdout, "void printSetWithMessage(const string& mySTR, const string& message) {\n");
    fprintf(stdout, "    cout << message << \" \\\"\" << mySTR << \"\\\"\" << endl;\n");
    fprintf(stdout, "}\n");

    
    fprintf(stdout, "//input from the user for each identifier type\n");
    fprintf(stdout, "void input_from_user(const string &massage, int &identifier) {\n");
    fprintf(stdout, "    cout << massage;\n");
    fprintf(stdout, "    cin >> identifier;\n");
    fprintf(stdout, "}\n");

    fprintf(stdout, "void input_from_user(const string &massage, string &identifier) {\n");
    fprintf(stdout, "    cout << massage;\n");
    fprintf(stdout, "    cin >> identifier;\n");
    fprintf(stdout, "}\n");

    fprintf(stdout, "void input_from_user(const string &message, set<string> &words) {\n");
    fprintf(stdout, "    cout << message;\n");
    fprintf(stdout, "    cin.clear();\n");
    fprintf(stdout, "\n");
    fprintf(stdout, "    string temp;\n");
    fprintf(stdout, "    getline(cin, temp);\n");
    fprintf(stdout, "    words.clear();\n");
    fprintf(stdout, "\n");
    fprintf(stdout, "    if (!temp.empty() && (temp.front() == '{' && temp.back() == '}')) {\n");
    fprintf(stdout, "        temp = temp.substr(1, temp.size() - 2);\n");
    fprintf(stdout, "    }\n");
    fprintf(stdout, "\n");
    fprintf(stdout, "    string temp_word;\n");
    fprintf(stdout, "    bool in_quotes = false;\n");
    fprintf(stdout, "\n");
    fprintf(stdout, "    for (size_t i = 0; i < temp.size(); ++i) {\n");
    fprintf(stdout, "        if (temp[i] == '\\\"') {\n");
    fprintf(stdout, "            in_quotes = !in_quotes;\n");
    fprintf(stdout, "        } else if (temp[i] == ',' && !in_quotes) {\n");
    fprintf(stdout, "            temp_word.erase(temp_word.find_last_not_of(\" \\t\") + 1);\n");
    fprintf(stdout, "            if (!temp_word.empty()) {\n");
    fprintf(stdout, "                if (temp_word.front() != '\\\"' && temp_word.back() != '\\\"') {\n");
    fprintf(stdout, "                    words.insert(temp_word);\n");
    fprintf(stdout, "                } else {\n");
    fprintf(stdout, "                    temp_word.erase(0, temp_word.find_first_not_of('\\\"'));\n");
    fprintf(stdout, "                    temp_word.erase(temp_word.find_last_not_of('\\\"') + 1);\n");
    fprintf(stdout, "                    if (!temp_word.empty()) {\n");
    fprintf(stdout, "                        words.insert(temp_word);\n");
    fprintf(stdout, "                    }\n");
    fprintf(stdout, "                }\n");
    fprintf(stdout, "                temp_word.clear();\n");
    fprintf(stdout, "            }\n");
    fprintf(stdout, "        } else if (temp[i] == ' ' && !in_quotes) {\n");
    fprintf(stdout, "            continue;\n");
    fprintf(stdout, "        } else {\n");
    fprintf(stdout, "            temp_word += temp[i];\n");
    fprintf(stdout, "        }\n");
    fprintf(stdout, "    }\n");
    fprintf(stdout, "    temp_word.erase(temp_word.find_last_not_of(\" \\t\") + 1);\n");
    fprintf(stdout, "    if (!temp_word.empty()) {\n");
    fprintf(stdout, "        if (temp_word.front() != '\\\"' && temp_word.back() != '\\\"') {\n");
    fprintf(stdout, "            words.insert(temp_word);\n");
    fprintf(stdout, "        } else {\n");
    fprintf(stdout, "            temp_word.erase(0, temp_word.find_first_not_of('\\\"'));\n");
    fprintf(stdout, "            temp_word.erase(temp_word.find_last_not_of('\\\"') + 1);\n");
    fprintf(stdout, "            if (!temp_word.empty()) {\n");
    fprintf(stdout, "                words.insert(temp_word);\n");
    fprintf(stdout, "            }\n");
    fprintf(stdout, "        }\n");
    fprintf(stdout, "    }\n");
    fprintf(stdout, "}\n");

    fprintf(stdout, "void input_from_user(const string &message, set<int> &numbers) {\n");
    fprintf(stdout, "    cout << message;\n");
    fprintf(stdout, "\n");
    fprintf(stdout, "    cin.clear();\n");
    fprintf(stdout, "\n");
    fprintf(stdout, "    string temp;\n");
    fprintf(stdout, "\n");
    fprintf(stdout, "    getline(cin, temp);\n");
    fprintf(stdout, "    numbers.clear();\n");
    fprintf(stdout, "\n");
    fprintf(stdout, "    if (!temp.empty() && temp.front() == '[' && temp.back() == ']') {\n");
    fprintf(stdout, "        temp = temp.substr(1, temp.size() - 2);\n");
    fprintf(stdout, "    }\n");
    fprintf(stdout, "\n");
    fprintf(stdout, "    string temp_number;\n");
    fprintf(stdout, "    for (size_t i = 0; i < temp.size(); ++i) {\n");
    fprintf(stdout, "        if (isdigit(temp[i]) || (temp[i] == '-' && i + 1 < temp.size() && isdigit(temp[i + 1]))) {\n");
    fprintf(stdout, "            temp_number += temp[i];\n");
    fprintf(stdout, "        } else if (temp[i] == ',' || temp[i] == ' ') {\n");
    fprintf(stdout, "            if (!temp_number.empty()) {\n");
    fprintf(stdout, "                numbers.insert(stoi(temp_number));\n");
    fprintf(stdout, "                temp_number.clear();\n");
    fprintf(stdout, "            }\n");
    fprintf(stdout, "        }\n");
    fprintf(stdout, "    }\n");
    fprintf(stdout, "    if (!temp_number.empty()) {\n");
    fprintf(stdout, "        numbers.insert(stoi(temp_number));\n");
    fprintf(stdout, "    }\n");
    fprintf(stdout, "}\n");


    fprintf(stdout, "void printSetWithMessage(const string& message) {\n");
    fprintf(stdout, "    cout << message << endl;\n");
    fprintf(stdout, "}\n");
    
    fprintf(stdout, "int main()\n");
    fprintf(stdout, "{\n");
    yyparse();

    fprintf(stdout, "}\n");
    if (fclose(outputFile) != 0) {
        fprintf(stderr, "Error closing output file.\n");
    }
    if (fclose(inputFile) != 0) {
        fprintf(stderr, "Error closing input file.\n");
    }

}
