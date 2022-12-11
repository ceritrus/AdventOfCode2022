#ifndef DEBUG
# define DEBUG 0
#endif
#include <iostream>
#include <vector>
#include <boost/function.hpp>
using namespace std;

class Monkey {
    public:
        Monkey(vector<unsigned long int> inv, string sec, function<int(int, int)> ope, int div, int it, int iff) {
            inventory = inv;
            second = sec;
            this->op = ope;
            opcount = 0;
            iftrue = it;
            iffalse = iff;
            divisible = div;
        }

        unsigned long int doop(unsigned long int a) {
            if (second == "old")
                return (op(a, a));
            else
                return (op(a, stoi(second)));
        }

        string second;
        vector<unsigned long int> inventory;
        boost::function<unsigned long int(unsigned long int, unsigned long int)> op;
        unsigned long int opcount;
        unsigned long int divisible;
        int iftrue;
        int iffalse;
};

void monkeybusiness(vector<Monkey> &monkeys) {
    int i = -1;
    for (Monkey &man : monkeys) {
        i++;
        //cerr << "\tMonkey " << i << endl;
        while (man.inventory.size() > 0) {
            man.opcount += 1;
            //cerr << "\t\tMonkey inspects an item with a worry level of " << man.inventory[0] << endl;
            man.inventory[0] = man.doop(man.inventory[0]);
            //cerr << "\t\t\tAfter operation: " << man.inventory[0] << endl;
            //man.inventory[0] /= 3;
            //cerr << "\t\t\tMonkey gets bored with item. Worry level is now " << man.inventory[0] << endl;
            if (man.inventory[0] % man.divisible == 0) {
                //cerr << "\t\t\tCurrent worry level is divisible by " << man.divisible << endl;
                //cerr << "\t\t\tItem with worry level " << man.inventory[0] << " is given to monkey " << man.iftrue << endl;
                monkeys[man.iftrue].inventory.push_back(man.inventory[0]);
            }
            else {
                //cerr << "\t\t\tCurrent worry level isn't divisible by " << man.divisible << endl;
                //cerr << "\t\t\tItem with worry level " << man.inventory[0] << " is given to monkey " << man.iffalse << endl;
                monkeys[man.iffalse].inventory.push_back(man.inventory[0]);;
            }
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
            vector<unsigned long int> inv;
            size_t j = 0;
            while (j != string::npos) {
                if (j != 0)
                    input[i + 1].erase(0, j + 1);
                inv.push_back(stoi(input[i + 1]));
                j = input[i + 1].find(" ");
            }
            input[i + 2].erase(0, input[i + 2].find("=") + 2);
            input[i + 2].erase(0, input[i + 2].find("= old") + 5);
            boost::function<unsigned long int(unsigned long int, unsigned long int)> ope;
            if (input[i + 2][0] == '+')
                ope = plus<unsigned long int>();
            else if (input[i + 2][0] == '-')
                ope = minus<unsigned long int>();
            else if (input[i + 2][0] == '*')
                ope = multiplies<unsigned long int>();
            else if (input[i + 2][0] == '/')
                ope = divides<unsigned long int>();
            else if (input[i + 2][0] == '%')
                ope = modulus<unsigned long int>();
            input[i + 2].erase(0, 2);
            input[i + 3].erase(0, input[i + 3].find("by ") + 3);
            unsigned long int divisible = stoi(input[i + 3]);
            input[i + 4].erase(0, input[i + 4].find("monkey ") + 7);
            int iftrue = stoi(input[i + 4]);
            input[i + 5].erase(0, input[i + 5].find("monkey ") + 7);
            int iffalse = stoi(input[i + 5]);
            monkeys.push_back(Monkey(inv, input[i + 2], ope, divisible, iftrue, iffalse));
            monkey++;
        }
    }
    for (int round = 0; round < 10000; round++)
        monkeybusiness(monkeys);
    unsigned long int max[2] = {0, 0};
    for (size_t i = 0; i < monkeys.size(); i++) {
        cerr << "Monkey " << i << " did " << monkeys[i].opcount << " operations" << endl;
        if (monkeys[i].opcount > max[0]) {
            if (monkeys[i].opcount > max[1]) {
                max[0] = max[1];
                max[1] = monkeys[i].opcount;
            }
            else
                max[0] = monkeys[i].opcount;
        }
    }
    cerr << "Max: ---------------" << endl;
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