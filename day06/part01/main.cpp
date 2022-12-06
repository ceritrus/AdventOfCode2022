#ifndef DEBUG
# define DEBUG 0
#endif
#include <iostream>
#include <vector>
using namespace std;

void exec(vector<string> input) {
    // main code goes here
    int size = 4;
    for (auto line : input) {
        bool same;
        for (size_t i = size - 1; i < line.size(); i++) {
            same = false;
            for (int j = 0; j < size; j++) {
                for (int k = 0; k < size; k++) {
                    if (j != k) {
                        if (line[i - j] == line[i - k]) {
                            same = true;
                            break;
                        }
                    }
                }
                if (same)
                    break;
            }
            if (same == false) {
                std::cout << i + 1 << endl;
                return;
            }
        }
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