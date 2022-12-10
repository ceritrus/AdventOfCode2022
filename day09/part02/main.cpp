#ifndef DEBUG
# define DEBUG 0
#endif
#include <iostream>
#include <vector>
using namespace std;

int xdistance(pair <int, int> a, pair <int, int> b) {
    if (a.first > b.first)
        return (a.first - b.first);
    else
        return (b.first - a.first);
}

int ydistance(pair <int, int> a, pair <int, int> b) {
    if (a.second > b.second)
        return (a.second - b.second);
    else
        return (b.second - a.second);
}

int movetowards(int a, int b) {
    if (a > b)
        return (a - 1);
    else
        return (a + 1);
}

void movetail(pair<int, int> &head, pair<int, int> &tail) {
    if (xdistance(head, tail) > 1 && ydistance(head, tail) == 0) { // move x
        tail.first = movetowards(tail.first, head.first);
    }
    else if (xdistance(head, tail) == 0 && ydistance(head, tail) > 1) { // move y
        tail.second = movetowards(tail.second, head.second);
    }
    else if (xdistance(head, tail) > 1 || ydistance(head, tail) > 1) { // move diagonal
        tail.first = movetowards(tail.first, head.first);
        tail.second = movetowards(tail.second, head.second);
    }
}

void exec(vector<string> input) {
    vector<pair<int, int>> visited;
    pair<int, int> head = {50000, 50000};
    pair<int, int> tail[9];
    for (int i = 0; i < 9; i++)
        tail[i] = {50000, 50000};
    for (auto &line : input) {
        pair<char, int> move;
        move.first = line[0];
        line.erase(0, 2);
        move.second = stoi(line);
        for (int i = 0; i < move.second; i++) {
            if (move.first == 'U')
                head.second++;
            else if (move.first == 'D')
                head.second--;
            else if (move.first == 'R')
                head.first++;
            else if (move.first == 'L')
                head.first--;
            if (head != tail[0])
                movetail(head, tail[0]);
            for (int i = 1; i < 9; i++) {
                if (tail[i - 1] != tail[i])
                    movetail(tail[i - 1], tail[i]);
            }
            visited.push_back(tail[8]);
        }
    }
    for (size_t i = 0; i < visited.size(); i++) {
        for (size_t j = i + 1; j < visited.size(); j++) {
            if (visited[i] == visited[j]) {
                visited.erase(visited.begin() + j);
                j--;
            }
        }
    }
    int total = visited.size();
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