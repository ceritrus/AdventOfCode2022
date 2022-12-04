#ifndef DEBUG
# define DEBUG 0
#endif
#include <iostream>
#include <vector>
using namespace std;

void exec(vector<string> input) {
    // main code goes here
    int res = 0;
    for (string line : input) {
        string halves[2];
        int split = line.length() / 2;
        halves[0] = line.substr(0, split);
        halves[1] = line.substr(split, line.length());
        bool found = false;
        for (char a : halves[0]) {
            for (char b : halves[1]) {
                if (a == b && !found)
                {
                    res += (a >= 'a' && a <= 'z') ? a - 'a' + 1 : a - 'A' + 27;
                    found = true;
                    break;
                }
            }
            if (found)
                break;
        }
    }
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