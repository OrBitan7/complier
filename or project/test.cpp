#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>
#include <set>

using namespace std;

int main()
{
set<string> a;
set<string> b;
set<string> c;
{
a.insert("hi");
a.insert("lol");
}
{
b.insert("hi");
b.insert("ldsadaol");
}
{
   c.insert(b.begin(), b.end());
   c.insert(a.begin(), a.end());
}
{ 
   cout << "a:";
   cout << "{";
   bool first = true;
   for (const auto& item : a) {
       if (!first) {
           cout << ", ";
       }
      cout << item;
      first = false;
   }
   cout << "}" << endl;
}
{ 
   cout << "b:";
   cout << "{";
   bool first = true;
   for (const auto& item : b) {
       if (!first) {
           cout << ", ";
       }
      cout << item;
      first = false;
   }
   cout << "}" << endl;
}
{ 
   cout << "c:";
   cout << "{";
   bool first = true;
   for (const auto& item : c) {
       if (!first) {
           cout << ", ";
       }
      cout << item;
      first = false;
   }
   cout << "}" << endl;
}
}
