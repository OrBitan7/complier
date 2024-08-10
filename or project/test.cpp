#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>
#include <set>

#include <initializer_list>

using namespace std;

template <typename T>
set<T> make_literal(initializer_list<T> list)
{
    return set<T>(list);
}
// COLLECTION operators
set<string> operator-(const set<string> &set1, const set<string> &set2)
{
    set<string> result = set1;
    for (const string &elem : set2)
    {
        result.erase(elem);
    }
    return result;
}
set<string> operator+(const set<string> &set1, const set<string> &set2)
{
    set<string> result = set1;
    result.insert(set2.begin(), set2.end());
    return result;
}
set<string> operator+(const set<string> &set1, const string &str)
{
    set<string> result = set1;
    result.insert(str);
    return result;
}
set<string> operator*(const set<string> &set1, const set<string> &set2)
{
    set<string> result;
    for (const string &elem : set1)
    {
        if (set2.find(elem) != set2.end())
        {
            result.insert(elem);
        }
    }
    return result;
}
void printSetWithMessage(const set<string> &mySet, const string &message)
{
    cout << message << " {";
    auto it = mySet.begin();
    if (it != mySet.end())
    {
        cout << "\"" << *it << "\"";
        ++it;
    }
    while (it != mySet.end())
    {
        cout << ", \"" << *it << "\"";
        ++it;
    }
    cout << "}" << endl;
}
// SET operators
set<int> operator-(const set<int> &set1, const set<int> &set2)
{
    set<int> result = set1;
    for (const int &elem : set2)
    {
        result.erase(elem);
    }
    return result;
}
set<int> operator+(const set<int> &set1, const set<int> &set2)
{
    set<int> result = set1;
    result.insert(set2.begin(), set2.end());
    return result;
}
set<int> operator+(const set<int> &set1, const int &str)
{
    set<int> result = set1;
    result.insert(str);
    return result;
}
set<int> operator*(const set<int> &set1, const set<int> &set2)
{
    set<int> result;
    for (const int &elem : set1)
    {
        if (set2.find(elem) != set2.end())
        {
            result.insert(elem);
        }
    }
    return result;
}
void printSetWithMessage(const set<int> &mySet, const string &message)
{
    cout << message << " [";
    auto it = mySet.begin();
    if (it != mySet.end())
    {
        cout << *it;
        ++it;
    }
    while (it != mySet.end())
    {
        cout << "," << *it;
        ++it;
    }
    cout << "]" << endl;
}
// INT operators
int make_literal(int list)
{
    return list;
}
void printSetWithMessage(const int &myINT, const string &message)
{
    cout << message << " " << myINT << endl;
}
// STRING operators
string make_literal(string list)
{
    return list;
}
void printSetWithMessage(const string &mySTR, const string &message)
{
    cout << message << " \"" << mySTR << "\"" << endl;
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
    // Token: 'ID' = l
    // Token: 'symbol' = ,
    // Token: 'ID' = g
    // Token: 'symbol' = ;
    set<int> l, g;
    // Token: 'ID' = a
    // Token: 'symbol' = =
    // Token: '{'
    // Token: 'string' = "hi"
    // Token: 'symbol' = ,
    // Token: 'string' = "lol"
    // Token: '}'
    // Token: 'symbol' = ;
    a = (make_literal<string>({"hi", "lol"}));
    // Token: 'ID' = b
    // Token: 'symbol' = =
    // Token: '{'
    // Token: '}'
    // Token: 'symbol' = ;
    b = (make_literal<string>({}));
    // Token: 'ID' = x
    // Token: 'symbol' = =
    // Token: 'int' = 5
    // Token: 'symbol' = ;
    x = (make_literal(5));
    // Token: 'ID' = g
    // Token: 'symbol' = =
    // Token: '['
    // Token: 'int' = 1
    // Token: 'symbol' = ,
    // Token: 'int' = 2
    // Token: 'symbol' = ,
    // Token: 'int' = 4
    // Token: 'symbol' = ,
    // Token: 'int' = 5
    // Token: 'symbol' = ,
    // Token: 'int' = 6
    // Token: ']'
    // Token: 'symbol' = ;
    g = (make_literal<int>({1, 2, 4, 5, 6}));
    // Token: '{'
    // Token: 'ID' = l
    {
        // Token: 'symbol' = =
        // Token: '['
        // Token: ']'
        // Token: 'symbol' = ;
        l = (make_literal<int>({}));
        // Token: '}'
    }
    // Token: 'ID' = c
    // Token: 'symbol' = =
    // Token: 'ID' = a
    // Token: 'symbol' = &
    // Token: 'ID' = b
    // Token: 'symbol' = ;
    c = a;
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
    c = a;
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
    c = c;
    // Token: 'output'
    // Token: 'string' = "hess"
    // Token: 'ID' = c
    // Token: 'symbol' = -
    // Token: 'ID' = b
    // Token: 'symbol' = ;
}
