#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>

/* instruction */
enum Inst {
    nop = 0x1,
    acc = 0x2,
    jmp = 0x4,
};

/* operation */
struct Op {
    Inst inst = Inst::nop;
    int val;

    Op() = default;
    Op(Inst instruction, int v) : inst(instruction), val(v) {}
};

bool walkBackwards(std::list<int> &instructions,
        std::vector<Op> &vec, std::map<int,bool> &ran, int ret)
{
    int previous;
    Inst savedInst;
    while (!instructions.empty()) {
        previous = instructions.back();
        instructions.pop_back();
        printf("\t# checking %d\n", previous);
        ran[previous] = false;

        if (vec[previous].inst == acc) {
            ret -= vec[previous].val;
            continue;
        } else if (vec[previous].inst == jmp) {
            savedInst = jmp;
            vec[previous].inst = nop;
        } else if (vec[previous].inst == nop) {
            savedInst = nop;
            vec[previous].inst = jmp;
        }
        break;
    }

    printf("\t# previous found: %d\n", previous);

    auto it = vec.begin() + previous;
    while (it != vec.end()) {
        int index = it-vec.begin();
        if (ran.count(index) && ran[index] == true) {
            // didn't work, revert changes and try again
            printf("# %ld : ran already, returning\n", it-vec.begin());
            vec[previous].inst = savedInst;
            return false;
        }
        printf("# %ld : %d\n", it - vec.begin(), ret);
        if (it->inst == acc) {
            ret += it->val;
        }

        if (it->inst == jmp) {
            it += it->val;
        } else {
            it++;
        }
        ran[index] = true;
    }
    printf("found ending? : %d\n", ret);
    return true;
}

int main() {
    // array of operations
    std::vector<Op> vec;

    // 1st pass load it
    for (std::string line; std::getline(std::cin, line) && !line.empty(); ) {
        if (line.find("nop") != std::string::npos) {
            vec.push_back({});
        } else if (line.find("acc") != std::string::npos) {
            int val = std::stoi(line.substr(5));
            val = (line[4] == '-' ? -val : val);
            vec.push_back({acc, val});
        } else if (line.find("jmp") != std::string::npos) {
            int val = std::stoi(line.substr(5));
            val = (line[4] == '-' ? -val : val);
            vec.push_back({jmp, val});
        } else {
            throw("uh");
        }
    }

    int ret = 0;
    std::map<int,bool> ran;
    std::list<int> instructions;

    for (auto it = vec.begin(); it != vec.end(); ) {
        int index = it-vec.begin();
        if (ran.count(index) && ran[index]) {
            // part 1.
            printf("# %ld : ran already, exiting\n", it-vec.begin());
            printf("ans 1: %d\n", ret);
            // return(0);

            // part 2:
            // start walking backwards throught the list of previous commands,
            // try switching nops/jmps until we stop repeating instructions.
            printf("# %ld : ran already, walking backwards\n", it-vec.begin());
            while (!walkBackwards(instructions, vec, ran, ret)) {
                printf("not found : %d\n", index);
            }
            return 0;
        }

        printf("# %ld : %d\n", it - vec.begin(), ret);
        if (it->inst == acc) {
            ret += it->val;
        }

        if (it->inst == jmp) {
            it += it->val;
        } else {
            it++;
        }

        ran[index] = true;
        instructions.push_back(index);
    }

    return 0;
}
