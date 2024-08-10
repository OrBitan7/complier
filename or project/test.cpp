#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>
#include <set>

#include <initializer_list>

using namespace std;

//COLLECTION operators
set<string> make_literal(initializer_list<string> list) {
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
set<int> make_literal(initializer_list<int> list) {
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
//INT operators
int make_literal(int list) {
    return list;
}
//STRING operators
string make_literal(string list) {
    return list;
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
set<string> a, b, c;
// Token: 'int'
// Token: 'ID' = x
// Token: 'symbol' = ;
int x;
// Token: 'int'
// Token: 'ID' = y
// Token: 'symbol' = ,
// Token: 'ID' = u
// Token: 'symbol' = ;
int y, u;
// Token: 'str'
// Token: 'ID' = o
// Token: 'symbol' = ,
// Token: 'ID' = afdsd
// Token: 'symbol' = ;
string o, afdsd;
// Token: 'set'
// Token: 'ID' = lpqwe
// Token: 'symbol' = ,
// Token: 'ID' = gggg
// Token: 'symbol' = ;
set<int> lpqwe, gggg;
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
// Token: 'symbol' = =
// Token: '{'
// Token: 'string' = "hi"
// Token: 'symbol' = ,
// Token: 'string' = "m"
// Token: '}'
// Token: 'symbol' = ;
// Token: 'ID' = c
// Token: 'symbol' = =
// Token: 'ID' = a
// Token: 'symbol' = &
// Token: 'ID' = b
// Token: 'symbol' = ;
// Token: 'ID' = c
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
// Token: 'ID' = c
// Token: 'symbol' = |
// Token: 'symbol' = ;
// Token: 'ID' = c
// Token: 'symbol' = =
// Token: 'ID' = c
// Token: 'symbol' = -
// Token: 'string' = "lol"
// Token: 'symbol' = ;
// Token: 'output'
// Token: 'string' = "hess"
// Token: 'ID' = c
// Token: 'symbol' = -
// Token: 'ID' = b
// Token: 'symbol' = ;
}
