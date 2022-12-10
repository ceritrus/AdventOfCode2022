#ifndef DEBUG
# define DEBUG 0
#endif
#include <iostream>
#include <vector>
using namespace std;

int width;
int height;

void rotate(vector<string> &input, vector<vector<bool>> &grid)
{
    vector<string> output;
    for (int i = 0; i < width; i++) {
        string line;
        for (int j = height - 1; j >= 0; j--) {
            line += input[j][i];
        }
        output.push_back(line);
    }
    input = output;
    vector<vector<bool>> gridoutput;
    for (int i = 0; i < width; i++) {
        vector<bool> line;
        for (int j = height - 1; j >= 0; j--) {
            line.push_back(grid[j][i]);
        }
        gridoutput.push_back(line);
    }
    grid = gridoutput;
}

void spot(vector<string> &input, vector<vector<bool>> &grid)
{
    for (int i = 0; i < height; i++) {
        int tallest = 0;
        for (int j = 0; j < width; j++) {
            if (input[i][j] > tallest) {
                tallest = input[i][j];
                grid[i][j] = true;
            }
        }
    }
}

int count (vector<vector<bool>> grid)
{
    int count = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (grid[i][j])
                count++;
        }
    }
    return count;
}

void exec(vector<string> input) {
    width = input[0].length();
    height = input.size();
    vector<vector<bool>> visible;
    for (int i = 0; i < height; i++) {
        vector<bool> line;
        for (int j = 0; j < width; j++)
            line.push_back(false);
        visible.push_back(line);
    }
    for (int i = 0; i < 4; i++) {
        spot(input, visible);
        rotate(input, visible);
    }
    if (DEBUG) {
        for (vector<bool> line : visible) {
            for (bool pixel : line) {
                if (pixel)
                    cerr << "X";
                else
                    cerr << " ";
            }
            cerr << endl;
        }
        cerr << endl;
    }
    cout << count(visible) << endl;
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