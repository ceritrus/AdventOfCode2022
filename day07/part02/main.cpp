#ifndef DEBUG
# define DEBUG 0
#endif
#include <iostream>
#include <vector>
using namespace std;

vector<string> path;
vector<pair<vector<string>, int>> directories;

void cd(string line) {
    line.erase(0,3);
    if (line == "/")
        path.clear();
    else if (line == "..") {
        path.pop_back();
    } else
        path.push_back(line);
}

bool dircheck(vector<string> path) {
    for (auto dir : directories) {
        if (dir.first == path)
            return (true);
    }
    return (false);
}

int checktree(vector<string> dirpath) {
    int size = 0;
    for (auto dir : directories) {
        if (dir.first.size() == dirpath.size() + 1) {
            bool same = true;
            for (size_t i = 0; i < dirpath.size(); i++) {
                if (dir.first[i] != dirpath[i]) {
                    same = false;
                    break;
                }
            }
            if (same) {
                dir.second += checktree(dir.first);
                size += dir.second;
            }
        }
    }
    return (size);
    
}

void exec(vector<string> input) {
    vector<string> lshead;
    for (auto line : input) {
        if (line[0] == '$') {
            lshead.clear();
            line.erase(0,2);
            if (line.find("cd") == 0)
                cd(line);
            else if (line.find("ls") == 0) {
                if (!dircheck(path)) {
                    lshead = path;
                    directories.push_back(make_pair(path, 0));
                }
            }
        }
        else if ((!lshead.empty() || path.empty()) && line.find("dir") != 0)
            directories.back().second += stoi(line);
    }
    for (size_t i = 0; i < directories.size(); i++)
        directories[i].second += checktree(directories[i].first);
    int freespace = 70000000 - directories[0].second;
    int minsize = 30000000 - freespace;
    int res = 70000000;
    for (auto dir : directories) {
        if (dir.second >= minsize && dir.second < res)
            res = dir.second;
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