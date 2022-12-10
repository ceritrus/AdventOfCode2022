#ifndef DEBUG
# define DEBUG 0
#endif
#include <iostream>
#include <vector>
using namespace std;

void exec(vector<string> input) {
    int reg = 1;
    int clock = 1;
    vector<char> screen;
    for (auto &line : input) {
        int duration = 0;
        if (line.find("addx") != string::npos)
            duration = 2;
        else if (line.find("noop") != string::npos)
            duration = 1;
        while (duration > 0) {
            duration--;
            int cursor = (clock - 1) % 40;
            if (reg - cursor <= 1 && reg - cursor >= -1)
                screen.push_back('#');
            else
                screen.push_back(' ');
            if (duration == 0 && line.find("addx") != string::npos) {
                line.erase(0, 5);
                reg += stoi(line);
            }
            clock++;
        }
    }
    for (size_t i = 0; i < screen.size(); i++) {
        cout << screen[i];
        if ((i + 1) % 40 == 0)
            cout << endl;
    }
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