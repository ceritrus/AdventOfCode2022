#ifndef DEBUG
# define DEBUG 0
#endif
#include <iostream>
#include <vector>
using namespace std;

int width;
int height;

int looknorth(vector<string> &input, int x, int y) {
    int count = 0;
    bool blocked = false;
    for (int i = y - 1; i >= 0; i--) {
        if (!blocked) {
            count++;
            if (input[i][x] >= input[y][x])
                blocked = true;
        }
    }
    if (DEBUG)
        cerr << "\tNorth: " << count << endl;
    return count;
}

int looksouth(vector<string> &input, int x, int y) {
    int count = 0;
    bool blocked = false;
    for (int i = y + 1; i < height; i++) {
        if (!blocked) {
            count++;
            if (input[i][x] >= input[y][x])
                blocked = true;
        }
    }
    if (DEBUG)
        cerr << "\tSouth: " << count << endl;
    return count;
}

int lookwest(vector<string> &input, int x, int y) {
    int count = 0;
    bool blocked = false;
    for (int i = x - 1; i >= 0; i--) {
        if (!blocked) {
            count++;
            if (input[y][i] >= input[y][x])
                blocked = true;
        }
    }
    if (DEBUG)
        cerr << "\tWest: " << count << endl;
    return count;
}

int lookeast(vector<string> &input, int x, int y) {
    int count = 0;
    bool blocked = false;
    for (int i = x + 1; i < width; i++) {
        if (!blocked) {
            count++;
            if (input[y][i] >= input[y][x])
                blocked = true;
        }
    }
    if (DEBUG)
        cerr << "\tEast: " << count << endl;
    return count;
}

void spot(vector<string> &input, vector<vector<int>> &score) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int dir[4] = {0, 0, 0, 0};
            if (DEBUG)
                cerr << "Looking at tree: " << x << ", " << y << endl;
            dir[0] = looknorth(input, x, y);
            dir[1] = looksouth(input, x, y);
            dir[2] = lookwest(input, x, y);
            dir[3] = lookeast(input, x, y);
            score[y][x] = dir[0] * dir[1] * dir[2] * dir[3];
            if (DEBUG)
                cerr << "\tScore: " << score[y][x] << endl;
        }
    }
}

int bestscore(vector<vector<int>> score) {
    int best = 0;
    int bestx = 0;
    int besty = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (score[i][j] > best) {
                best = score[i][j];
                bestx = j;
                besty = i;
            }
        }
    }
    if (DEBUG)
        cerr << "Best spot: " << bestx << ", " << besty << " with score " << best << endl;
    return best;
}

void exec(vector<string> input) {
    width = input[0].length();
    height = input.size();
    vector<vector<int>> score;
    for (int i = 0; i < height; i++) {
        vector<int> line;
        for (int j = 0; j < width; j++)
            line.push_back(0);
        score.push_back(line);
    }
    spot(input, score);
    cout << bestscore(score) << endl;
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
                        cerr << "newline" << endl;
                    else if (DEBUG)
                        cerr << line << endl;
                }
            }
        }
        exec(input);
        return (0);
    }
    return (1);
}