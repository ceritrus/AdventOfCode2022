#ifndef DEBUG
# define DEBUG 0
#endif
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void exec(vector<string> input) {
    // main code goes here
    int stackcount = 9;
    vector<char> stacks[stackcount];
    for (string line : input) {
        if (line.find("[") != string::npos) {
            int curcount = -1;
            while (++curcount < stackcount) {
                if (line.at(curcount * 4 + 1) != ' ')
                    stacks[curcount].push_back(line.at(curcount * 4 + 1));
            }
        }
        else if (line == "") {
            for (int i = 0; i < stackcount; i++)
                reverse(stacks[i].begin(), stacks[i].end());
        }
        else if (line.find("move") == 0) {
            int qt, from, to;
            line.erase(0, 5);
            qt = stoi(line);
            line.erase(0, line.find("m") + 2);
            from = stoi(line) - 1;
            line.erase(0, line.find("o") + 2);
            to = stoi(line) - 1;
            for (int i = 0; i < qt; i++) {
                stacks[to].push_back(stacks[from].back());
                stacks[from].pop_back();
            }
        }
    }
    for (int i = 0; i < stackcount; i++)
        cout << stacks[i].back();
    cout << endl;
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