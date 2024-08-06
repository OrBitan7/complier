#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>
#include <set>

#include <initializer_list>

using namespace std;

//COLLECTION operators
set<string> make_collection(initializer_list<string> list) {
    return set<string>(list);
}
set<string> operator-(const set<string>& set1, const set<string>& set2) {
    set<string> result = set1;
    for (const string& elem : set2) {
        result.erase(elem);
    }
    return result;
}
set<string> operator+(const set<string>& set1, const set<string>& set2) {
    set<string> result = set1;
    result.insert(set2.begin(), set2.end());
    return result;
}
set<string> operator+(const set<string>& set1, const string& str) {
    set<string> result = set1;
    result.insert(str);
    return result;
}
set<string> operator*(const set<string>& set1, const set<string>& set2) {
    set<string> result;
    for (const string& elem : set1) {
        if (set2.find(elem) != set2.end()) {
            result.insert(elem);
        }
    }
    return result;
}
//SET operators
set<int> make_Set(initializer_list<int> list) {
    return set<int>(list);
}
set<int> operator-(const set<int>& set1, const set<int>& set2) {
    set<int> result = set1;
    for (const int& elem : set2) {
        result.erase(elem);
    }
    return result;
}
set<int> operator+(const set<int>& set1, const set<int>& set2) {
    set<int> result = set1;
    result.insert(set2.begin(), set2.end());
    return result;
}
set<int> operator+(const set<int>& set1, const int& str) {
    set<int> result = set1;
    result.insert(str);
    return result;
}
set<int> operator*(const set<int>& set1, const set<int>& set2) {
    set<int> result;
    for (const int& elem : set1) {
        if (set2.find(elem) != set2.end()) {
            result.insert(elem);
        }
    }
    return result;
}
int main()
{
set<string> a;
set<string> b;
set<string> c;
a=make_collection({"hi","lol"})+make_collection({"my","name"});
b=make_collection({"hi","m"});
c=a*b;
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
set<int> x;
set<int> y;
set<int> z;
x=make_Set({1,2,3,4,5,6});
y=x-make_Set({1,2,3,4});
z=x*y;
}
