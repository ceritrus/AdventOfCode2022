#ifndef DEBUG
# define DEBUG 0
#endif
#include <iostream>
#include <vector>
using namespace std;

void exec(vector<string> input) {
    // main code goes here
    int res = 0;
    int i = -1;
    string parts[3];
    for (string line : input) {
        parts[++i % 3] = line;
        if (i % 3 == 2 && i >= 2)
        {
            bool found = false;
            for (char first : parts[0]) {
                for (char second : parts[1]) {
                    if (first == second) {
                        for (char third : parts[2]) {
                            if (first == third) {
                                res += (first >= 'a' && first <= 'z') ? first - 'a' + 1 : first - 'A' + 27;
                                found = true;
                                break;
                            }
                        }
                    }
                    if (found) break;
                }
                if (found) break;
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