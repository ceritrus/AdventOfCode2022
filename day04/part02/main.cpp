#ifndef DEBUG
# define DEBUG 0
#endif
#include <iostream>
#include <vector>
using namespace std;

int overlap(int first[2], int second[2]) {
    if (first[0] >= second[0] && first[0] <= second[1])
        return (1);
    else if (first[1] >= second[0] && first[1] <= second[1])
        return (1);
    else if (second[0] >= first[0] && second[0] <= first[1])
        return (1);
    else if (second[1] >= first[0] && second[1] <= first[1])
        return (1);
    return (0);
}

void extract_pair(string line, int *pair) {
    pair[0] = stoi(line);
    line.erase(0, line.find("-") + 1);
    pair[1] = stoi(line);
}

void exec(vector<string> input) {
    // main code goes here
    int total = 0;
    for (string line : input) {
        int first[2];
        int second[2];
        extract_pair(line, first);
        line.erase(0, line.find(",") + 1);
        extract_pair(line, second);
        if (overlap(first, second))
            total += 1;
    }
    cout << total << endl;
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