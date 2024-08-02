#include <iostream>
#include <string>
typedef enum {Collection=1, Set} varType;
using namespace std;
class SymTable {
	string name;
	varType typ;
} SymTable[100];

