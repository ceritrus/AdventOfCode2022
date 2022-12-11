#ifndef DEBUG
# define DEBUG 0
#endif
#include <iostream>
#include <vector>
#include <boost/function.hpp>
using namespace std;

class Monkey {
    public:
        Monkey(vector<int> inv, string sec, function<int(int, int)> ope, int div, int it, int iff) {
            inventory = inv;
            second = sec;
            this->op = ope;
            opcount = 0;
            iftrue = it;
            iffalse = iff;
            divisible = div;
        }

        int doop(int a) {
            if (second == "old")
                return (op(a, a));
            else
                return (op(a, stoi(second)));
        }

        string second;
        vector<int> inventory;
        boost::function<int(int, int)> op;
        int opcount;
        int divisible;
        int iftrue;
        int iffalse;
};

void monkeybusiness(vector<Monkey> &monkeys) {
    int i = -1;
    for (Monkey &man : monkeys) {
        i++;
        while (man.inventory.size() > 0) {
            man.opcount += 1;
            man.inventory[0] = man.doop(man.inventory[0]);
            man.inventory[0] /= 3;
            if (man.inventory[0] % man.divisible == 0)
                monkeys[man.iftrue].inventory.push_back(man.inventory[0]);
            else
                monkeys[man.iffalse].inventory.push_back(man.inventory[0]);;
            man.inventory.erase(man.inventory.begin());
        }
    }
}
void exec(vector<string> input) {
    vector<Monkey> monkeys;
    int monkey = 0;
    for (size_t i = 0; i < input.size(); i++) {
        if (input[i].find("Monkey") != string::npos) {
            input[i + 1].erase(0, input[i + 1].find(":") + 2);
            vector<int> inv;
            size_t j = 0;
            while (j != string::npos) {
                if (j != 0)
                    input[i + 1].erase(0, j + 1);
                inv.push_back(stoi(input[i + 1]));
                j = input[i + 1].find(" ");
            }
            input[i + 2].erase(0, input[i + 2].find("=") + 2);
            input[i + 2].erase(0, input[i + 2].find("= old") + 5);
            boost::function<int(int, int)> ope;
            if (input[i + 2][0] == '+')
                ope = plus<int>();
            else if (input[i + 2][0] == '-')
                ope = minus<int>();
            else if (input[i + 2][0] == '*')
                ope = multiplies<int>();
            else if (input[i + 2][0] == '/')
                ope = divides<int>();
            else if (input[i + 2][0] == '%')
                ope = modulus<int>();
            input[i + 2].erase(0, 2);
            input[i + 3].erase(0, input[i + 3].find("by ") + 3);
            int divisible = stoi(input[i + 3]);
            input[i + 4].erase(0, input[i + 4].find("monkey ") + 7);
            int iftrue = stoi(input[i + 4]);
            input[i + 5].erase(0, input[i + 5].find("monkey ") + 7);
            int iffalse = stoi(input[i + 5]);
            monkeys.push_back(Monkey(inv, input[i + 2], ope, divisible, iftrue, iffalse));
            monkey++;
        }
    }
    for (int round = 0; round < 20; round++)
        monkeybusiness(monkeys);
    int max[2] = {0, 0};
    for (size_t i = 0; i < monkeys.size(); i++) {
        if (monkeys[i].opcount > max[0]) {
            if (monkeys[i].opcount > max[1]) {
                max[0] = max[1];
                max[1] = monkeys[i].opcount;
            }
            else
                max[0] = monkeys[i].opcount;
        }
    }
    cout << max[0] * max[1] << endl;
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