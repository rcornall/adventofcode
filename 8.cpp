#include <iostream>
#include <string>
#include <vector>
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
    Op(Inst instruction) : inst(instruction) {}
    Op(Inst instruction, int v) : inst(instruction), val(v) {}
};

int main() {
    std::vector<Op> vec;

    // 1st pass
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

    for (auto it = vec.begin(); it != vec.end(); ) {
        int index = it-vec.begin();
        if (ran.count(index)) {
            printf("# %ld : ran already, exiting\n", it-vec.begin());
            printf("ret: %d\n", ret);
            return(0);
        }
        ran[index] = true;

        printf("# %ld : %d\n", it - vec.begin(), ret);
        if (it->inst == acc) {
            ret += it->val;
        }

        if (it->inst == jmp) {
            it += it->val;
        } else {
            it++;
        }
    }
}
