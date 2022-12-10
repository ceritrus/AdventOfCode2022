#ifndef DEBUG
# define DEBUG 0
#endif
#include <iostream>
#include <vector>
using namespace std;

void exec(vector<string> input) {
    int reg = 1;
    int clock = 0;
    int res = 0;
    for (auto &line : input) {
        int duration = 0;
        if (line.find("addx") != string::npos)
            duration = 2;
        else if (line.find("noop") != string::npos)
            duration = 1;
        while (duration > 0) {
            clock++;
            if (clock <= 220 && (clock == 20 || (clock - 20) % 40 == 0)) {
                if (DEBUG)
                    cout << "clock: " << clock << " reg: " << reg << endl;
                res += clock * reg;
            }
            duration--;
            if (duration == 0 && line.find("addx") != string::npos) {
                line.erase(0, 5);
                reg += stoi(line);
            }
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