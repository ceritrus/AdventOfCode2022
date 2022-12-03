#ifndef DEBUG
# define DEBUG 0
#endif
#include <bits/stdc++.h>
#include <iostream>
#include <vector>
using namespace std;

void exec(vector<string> input) {
    vector<int> calories;
    calories.push_back(0);
    for (string str : input) {
        if (str == "")
            calories.push_back(0);
        else
            calories.back() += stoi(str);
    }
    sort(calories.begin(), calories.end());
    int res = 0;
    for (size_t i = calories.size() - 3; i < calories.size(); i++)
       res += calories.at(i);
    cout << res << endl;
}

int main(int argc, char **argv) {
    string rawinput;
    if (argc < 2)
        cerr << "Error: missing argument" << endl;
    else if (argc > 2)
        cerr << "Error: too many arguments" << endl;
    else {
        vector<string> input;
        { // parsing
            rawinput = string(argv[1]);
            size_t i = 0;
            while ((i = rawinput.find("\n")) != string::npos) {
                input.push_back(rawinput.substr(0, i));
                rawinput.erase(0, i + 1);
            }
            input.push_back(rawinput.substr(0, i));
            if (DEBUG) {
                for (string line : input) {
                    if (line == "")
                        cout << "newline" << endl;
                    else if (DEBUG)
                        cout << line << endl;
                }
            }
        }
        exec(input);
        return (0);
    }
    return (1);
}