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
// input from the user for each identifier type
void input_from_user(const string &massage, int &identifier)
{
    cout << massage;
    cin >> identifier;
}
void input_from_user(const string &massage, string &identifier)
{
    cout << massage;
    cin >> identifier;
}
void input_from_user(const string &message, set<string> &words)
{
    cout << message;

    // Skip any leftover newline characters from previous input
    if (cin.peek() == '\n')
    {
        cin.ignore();
    }

    string temp;
    getline(cin, temp);
    words.clear();

    if (!temp.empty() && (temp.front() == '{' && temp.back() == '}'))
    {
        temp = temp.substr(1, temp.size() - 2);
    }

    string temp_word;
    bool in_quotes = false;

    for (size_t i = 0; i < temp.size(); ++i)
    {
        if (temp[i] == '"')
        {
            in_quotes = !in_quotes;
        }
        else if (temp[i] == ',' && !in_quotes)
        {
            temp_word.erase(temp_word.find_last_not_of(" \t") + 1);
            if (!temp_word.empty())
            {
                if (temp_word.front() != '"' && temp_word.back() != '"')
                {
                    words.insert(temp_word);
                }
                else
                {
                    temp_word.erase(0, temp_word.find_first_not_of('"'));
                    temp_word.erase(temp_word.find_last_not_of('"') + 1);
                    if (!temp_word.empty())
                    {
                        words.insert(temp_word);
                    }
                }
                temp_word.clear();
            }
        }
        else if (temp[i] == ' ' && !in_quotes)
        {
            continue;
        }
        else
        {
            temp_word += temp[i];
        }
    }
    temp_word.erase(temp_word.find_last_not_of(" \t") + 1);
    if (!temp_word.empty())
    {
        if (temp_word.front() != '"' && temp_word.back() != '"')
        {
            words.insert(temp_word);
        }
        else
        {
            temp_word.erase(0, temp_word.find_first_not_of('"'));
            temp_word.erase(temp_word.find_last_not_of('"') + 1);
            if (!temp_word.empty())
            {
                words.insert(temp_word);
            }
        }
    }
}
void input_from_user(const string &message, set<int> &numbers)
{
    cout << message;

    cin.clear();

    string temp;

    getline(cin, temp);
    numbers.clear();

    if (!temp.empty() && temp.front() == '[' && temp.back() == ']')
    {
        temp = temp.substr(1, temp.size() - 2);
    }

    string temp_number;
    for (size_t i = 0; i < temp.size(); ++i)
    {
        if (isdigit(temp[i]) || (temp[i] == '-' && i + 1 < temp.size() && isdigit(temp[i + 1])))
        {
            temp_number += temp[i];
        }
        else if (temp[i] == ',' || temp[i] == ' ')
        {
            if (!temp_number.empty())
            {
                numbers.insert(stoi(temp_number));
                temp_number.clear();
            }
        }
    }
    if (!temp_number.empty())
    {
        numbers.insert(stoi(temp_number));
    }
}
void printSetWithMessage(const string &message)
{
    cout << message << endl;
}
int main()
{
    printSetWithMessage("=============EXAMPLE 2 :=============");
    {
        set<string> highTech, gaming;
        set<string> software, hardware, industrial;
        highTech = (make_literal<string>({"Apple", "Google", "Microsoft", "Nvidia", "Adobe", "Oracle", "Sap"}));
        highTech = highTech + (make_literal<string>({"PayPal", "Nice", "Amdocs", "OpenAI", "Ford", "Mercedes"}));
        gaming = (make_literal<string>({"Sony", "Apple", "Microsoft", "Google", "Nintendo", "Playtika"}));
        software = (make_literal<string>({"Apple", "Microsoft", "Oracle", "Google", "Sap", "PayPal", "Playtika", "Amdocs", "OpenAI"}));
        hardware = (make_literal<string>({"Apple", "Nice", "Sony", "Google", "Cummins", "Nucor", "Microsoft", "Nvidia"}));
        industrial = (make_literal<string>({"Caterpillar", "Cummins", "Nucor"}));
        printSetWithMessage(software * hardware, "Companies that sell hardware & software:");
        set<string> highSW;
        highSW = software * highTech;
        if (highSW == software)
            printSetWithMessage(highSW, "All software companies are high-tech companies:");
        else
            printSetWithMessage(highSW, "Not all software companies are high-tech companies:");
        highSW = highSW + (make_literal<string>({(make_literal("Playtika"))}));
        if (highSW == software)
            printSetWithMessage(highSW, "Now all software companies are high-tech companies:");
        else
            printSetWithMessage(highSW, "Not all software companies are high-tech companies:");
        printSetWithMessage(software + hardware, "Companies that do software or hardware:");
        if (industrial * software == (make_literal<string>({})))
            printSetWithMessage("No industrial companies sell software");
        printSetWithMessage(hardware - (software * gaming), "Companies that sell Hardware but not Gaming Software:");
    }
}
