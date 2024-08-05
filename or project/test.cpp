#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>
#include <set>

#include <initializer_list>

using namespace std;

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
int main()
{
set<string> a;
set<string> b;
set<string> asad;
a = make_collection({"hello","hi"})-a+a*b+make_collection({"hiiiii","dsfjk"})+make_collection({"hiiii"}) ;
}
