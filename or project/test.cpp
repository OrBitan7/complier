#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>
#include <set>

#include <sstream>

#include <algorithm>

#include <initializer_list>

using namespace std;

template<typename T>
set<T> make_literal(initializer_list<T> list) {
    return set<T>(list);
}
//COLLECTION operators
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
void printSetWithMessage(const int& myINT, const string& message) {
    cout << message << " " << myINT << endl;
}
//STRING operators
string make_literal(string list) {
    return list;
}
void printSetWithMessage(const string& mySTR, const string& message) {
    cout << message << " \"" << mySTR << "\"" << endl;
}
//input from the user for each identifier type
void input_from_user(const string &massage, int &identifier) {
    cout << massage;
    cin >> identifier;
}
void input_from_user(const string &massage, string &identifier) {
    cout << massage;
    cin >> identifier;
}
void input_from_user(const string &message, set<string> &words) {
    cout << message;
    cin.clear();

    string temp;
    getline(cin, temp);
    words.clear();

    if (!temp.empty() && (temp.front() == '{' && temp.back() == '}')) {
        temp = temp.substr(1, temp.size() - 2);
    }

    string temp_word;
    bool in_quotes = false;

    for (size_t i = 0; i < temp.size(); ++i) {
        if (temp[i] == '\"') {
            in_quotes = !in_quotes;
        } else if (temp[i] == ',' && !in_quotes) {
            temp_word.erase(temp_word.find_last_not_of(" \t") + 1);
            if (!temp_word.empty()) {
                if (temp_word.front() != '\"' && temp_word.back() != '\"') {
                    words.insert(temp_word);
                } else {
                    temp_word.erase(0, temp_word.find_first_not_of('\"'));
                    temp_word.erase(temp_word.find_last_not_of('\"') + 1);
                    if (!temp_word.empty()) {
                        words.insert(temp_word);
                    }
                }
                temp_word.clear();
            }
        } else if (temp[i] == ' ' && !in_quotes) {
            continue;
        } else {
            temp_word += temp[i];
        }
    }
    temp_word.erase(temp_word.find_last_not_of(" \t") + 1);
    if (!temp_word.empty()) {
        if (temp_word.front() != '\"' && temp_word.back() != '\"') {
            words.insert(temp_word);
        } else {
            temp_word.erase(0, temp_word.find_first_not_of('\"'));
            temp_word.erase(temp_word.find_last_not_of('\"') + 1);
            if (!temp_word.empty()) {
                words.insert(temp_word);
            }
        }
    }
}
void input_from_user(const string &message, set<int> &numbers) {
    cout << message;

    cin.clear();

    string temp;

    getline(cin, temp);
    numbers.clear();

    if (!temp.empty() && temp.front() == '[' && temp.back() == ']') {
        temp = temp.substr(1, temp.size() - 2);
    }

    string temp_number;
    for (size_t i = 0; i < temp.size(); ++i) {
        if (isdigit(temp[i]) || (temp[i] == '-' && i + 1 < temp.size() && isdigit(temp[i + 1]))) {
            temp_number += temp[i];
        } else if (temp[i] == ',' || temp[i] == ' ') {
            if (!temp_number.empty()) {
                numbers.insert(stoi(temp_number));
                temp_number.clear();
            }
        }
    }
    if (!temp_number.empty()) {
        numbers.insert(stoi(temp_number));
    }
}
void printSetWithMessage(const string& message) {
    cout << message << endl;
}
int main()
{
// Token: 'collection'
// Token: 'ID' = classs
// Token: 'symbol' = ,
// Token: 'ID' = highGradeStudents
// Token: 'symbol' = ,
// Token: 'ID' = lowGradeStudents
// Token: 'symbol' = ,
// Token: 'ID' = avgGradeStudents
// Token: 'symbol' = ;
set<string> classs, highGradeStudents, lowGradeStudents, avgGradeStudents;
// Token: 'set'
// Token: 'ID' = grades
// Token: 'symbol' = ,
// Token: 'ID' = gradesHigh
// Token: 'symbol' = ;
set<int> grades, gradesHigh;
// Token: 'int'
// Token: 'ID' = grd
// Token: 'symbol' = ;
int grd;
// Token: 'str'
// Token: 'ID' = student
// Token: 'symbol' = ;
string student;
// Token: 'ID' = classs
// Token: 'symbol' = =
// Token: '{'
// Token: 'string' = "Rafi_Suisa"
// Token: 'symbol' = ,
// Token: 'string' = "Tamar_Even"
// Token: 'symbol' = ,
// Token: 'string' = "Avi_Maoz"
// Token: 'symbol' = ,
// Token: 'string' = "Eli_Kamer"
// Token: 'symbol' = ,
// Token: 'string' = "Shlomit_Raz"
// Token: 'symbol' = ,
// Token: 'string' = "Haim_Mizrachi"
// Token: 'symbol' = ,
// Token: 'string' = "Moshe_Samocha"
// Token: 'symbol' = ,
// Token: 'string' = "Tali_Raban"
// Token: 'symbol' = ,
// Token: 'string' = "Sharon_Tal"
// Token: 'symbol' = ,
// Token: 'string' = "Gal_Elbaz"
// Token: '}'
// Token: 'symbol' = ;
classs = (make_literal<string>({"Rafi_Suisa", "Tamar_Even", "Avi_Maoz", "Eli_Kamer", "Shlomit_Raz", "Haim_Mizrachi", "Moshe_Samocha", "Tali_Raban", "Sharon_Tal", "Gal_Elbaz"}));
// Token: 'ID' = gradesHigh
// Token: 'symbol' = =
// Token: '['
// Token: ']'
// Token: 'symbol' = ;
gradesHigh = (make_literal<int>({}));
// Token: 'ID' = highGradeStudents
// Token: 'symbol' = =
// Token: '{'
// Token: '}'
// Token: 'symbol' = ;
highGradeStudents = (make_literal<string>({}));
// Token: 'for'
// Token: '('
// Token: 'ID' = student
// Token: 'symbol' = :
// Token: 'ID' = classs
// Token: ')'
for(const string& student : classs)
// Token: '{'
// Token: 'output'
{
// Token: 'string' = "Grade for:"
// Token: 'ID' = student
// Token: 'symbol' = ;
printSetWithMessage(student, "Grade for:");
// Token: 'input'
// Token: 'string' = ">"
// Token: 'ID' = grd
// Token: 'symbol' = ;
input_from_user(make_literal(">"),grd);
// Token: 'ID' = grades
// Token: 'symbol' = =
// Token: 'ID' = grades
// Token: 'symbol' = +
// Token: 'ID' = grd
// Token: 'symbol' = ;
grades = grades + (make_literal<int>({grd}));
// Token: 'if'
// Token: '('
// Token: 'ID' = grd
// Token: '>='
// Token: 'int' = 90
// Token: ')'
if(grd >= (make_literal(90)))
// Token: '{'
// Token: 'ID' = gradesHigh
{
// Token: 'symbol' = =
// Token: 'ID' = gradesHigh
// Token: 'symbol' = +
// Token: 'ID' = grd
// Token: 'symbol' = ;
gradesHigh = gradesHigh + (make_literal<int>({grd}));
// Token: 'ID' = highGradeStudents
// Token: 'symbol' = =
// Token: 'ID' = highGradeStudents
// Token: 'symbol' = +
// Token: 'ID' = student
// Token: 'symbol' = ;
highGradeStudents = highGradeStudents + (make_literal<string>({student}));
// Token: '}'
}
// Token: '}'
}
// Token: 'if'
// Token: '('
// Token: 'ID' = gradesHigh
// Token: ')'
if((gradesHigh).size())
// Token: '{'
// Token: 'output'
{
// Token: 'string' = "Number of top grades:"
// Token: 'symbol' = |
// Token: 'ID' = gradesHigh
// Token: 'symbol' = |
// Token: 'symbol' = ;
printSetWithMessage((gradesHigh).size(), "Number of top grades:");
// Token: 'output'
// Token: 'string' = "Top Grades are:"
// Token: 'ID' = gradesHigh
// Token: 'symbol' = ;
printSetWithMessage(gradesHigh, "Top Grades are:");
// Token: 'output'
// Token: 'string' = "High Grade Students are:"
// Token: 'ID' = highGradeStudents
// Token: 'symbol' = ;
printSetWithMessage(highGradeStudents, "High Grade Students are:");
// Token: '}'
}
// Token: 'input'
// Token: 'string' = "Low-grade students >"
// Token: 'ID' = lowGradeStudents
// Token: 'symbol' = ;
input_from_user(make_literal("Low-grade students >"),lowGradeStudents);
// Token: 'for'
// Token: '('
// Token: 'ID' = student
// Token: 'symbol' = :
// Token: 'ID' = lowGradeStudents
// Token: ')'
for(const string& student : lowGradeStudents)
// Token: 'output'
// Token: 'string' = "Get better next time:"
// Token: 'ID' = student
// Token: 'symbol' = ;
printSetWithMessage(student, "Get better next time:");
// Token: 'ID' = avgGradeStudents
// Token: 'symbol' = =
// Token: 'ID' = classs
// Token: 'symbol' = -
// Token: 'ID' = highGradeStudents
// Token: 'symbol' = -
// Token: 'ID' = lowGradeStudents
// Token: 'symbol' = ;
avgGradeStudents = classs - highGradeStudents - lowGradeStudents;
// Token: 'output'
// Token: 'string' = "Students with good grades:"
// Token: 'ID' = avgGradeStudents
// Token: 'symbol' = ;
printSetWithMessage(avgGradeStudents, "Students with good grades:");
}
