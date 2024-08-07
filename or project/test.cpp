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
void printSetWithMessage(const set<string>& mySet, const string& message) {
    cout << message << " {";
    auto it = mySet.begin();
    if (it != mySet.end()) {
        cout << "\"" << *it << "\"";
        ++it;
    }
    while (it != mySet.end()) {
        cout << ", \"" << *it << "\"";
        ++it;
    }
    cout << "}" << endl;
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
void printSetWithMessage(const set<int>& mySet, const string& message) {
    cout << message << " [";
    auto it = mySet.begin();
    if (it != mySet.end()) {
        cout << *it ;
        ++it;
    }
    while (it != mySet.end()) {
        cout << "," << *it ;
        ++it;
    }
    cout << "]" << endl;
}
int main()
{
// Token: 'collection'
// Token: 'ID' = a
// Token: 'symbol' = ,
// Token: 'ID' = b
// Token: 'symbol' = ,
// Token: 'ID' = c
// Token: 'symbol' = ;
set<string> temp;
set<string> b;
set<string> c;
// Token: 'ID' = a
// Token: 'symbol' = =
// Token: '{'
// Token: 'string' = "hi"
// Token: 'symbol' = ,
// Token: 'string' = "lol"
// Token: '}'
// Token: 'symbol' = +
// Token: '{'
// Token: 'string' = "my"
// Token: 'symbol' = ,
// Token: 'string' = "name"
// Token: '}'
// Token: 'symbol' = ;
// Token: 'ID' = b
a=make_collection({"hi","lol"})+make_collection({"my","name"});
// Token: 'symbol' = =
// Token: '{'
// Token: 'string' = "hi"
// Token: 'symbol' = ,
// Token: 'string' = "m"
// Token: '}'
// Token: 'symbol' = ;
// Token: 'ID' = c
b=make_collection({"hi","m"});
// Token: 'symbol' = =
// Token: 'ID' = a
// Token: 'symbol' = &
// Token: 'ID' = b
// Token: 'symbol' = ;
// Token: 'ID' = c
c=a*b;
// Token: 'symbol' = =
// Token: 'ID' = a
// Token: 'symbol' = +
// Token: 'ID' = a
// Token: 'symbol' = +
// Token: 'ID' = a
// Token: 'symbol' = +
// Token: 'ID' = b
// Token: 'symbol' = +
// Token: 'ID' = b
// Token: 'symbol' = +
// Token: 'ID' = a
// Token: 'symbol' = ;
// Token: 'symbol' = |
c=a+a+a+b+b+a;
// Token: 'ID' = c
// Token: 'symbol' = |
// Token: 'symbol' = ;
(c).size();
// Token: 'ID' = c
// Token: 'symbol' = =
// Token: 'ID' = c
// Token: 'symbol' = -
// Token: 'string' = "lol"
// Token: 'symbol' = ;
// Token: 'output'
c=c-make_collection({"lol"});
// Token: 'string' = "hess"
// Token: 'ID' = c
// Token: 'symbol' = -
// Token: 'ID' = b
// Token: 'symbol' = ;
printSetWithMessage(c-b, "hess");



}
