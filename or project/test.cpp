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
set<string> d;
{
a.insert("hi");
a.insert("lol");
}
{
b.insert("hi");
b.insert("ldsadaol");
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
   a = a;
   a.erase("hloww");
}
{
   a = a;
   a.erase("hi");
}
{ 
   cout << "a after remove:";
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
   cout << "b after remove:";
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
}
