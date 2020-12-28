#include <functional>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

/*
O O  + + +
| |  | | |
O O    +     ^
 O    +      |
 |    |      |
 O    G      Recurse upwards from G
*/

struct Bag {
    std::vector<std::reference_wrapper<struct Bag>> parentBags;
    // list of childs bags, with associated counts
    std::vector<std::pair<int, std::reference_wrapper<struct Bag>>> childBags;

    std::string bagname;
    int count = 0;

    bool containsGold = false;

    Bag() {};
    Bag(std::string b) { bagname = b; };
};

void recurse(std::vector<std::reference_wrapper<struct Bag>> &bags) {
    for (auto &b : bags) {
        if (!b.get().parentBags.empty()) {
            recurse(b.get().parentBags);
        }
        if (!b.get().containsGold) {
            printf("adding gold bag %s\n", b.get().bagname.c_str());
            b.get().containsGold = true;
        }
    }
}

// dg -> 2*db -> 2*dv.
           // -> 2*dz.
int delve(std::vector<std::pair<int, std::reference_wrapper<struct Bag>>> &bags) {
    int count = 0;
    for (auto &[c,b] : bags) {
        if (!b.get().childBags.empty()) {
            int tmp = delve(b.get().childBags);
            printf("delved %s: %d\n", b.get().bagname.c_str(), tmp);
            count += (tmp * c) + c;
        } else {
            printf("adding child bags %s, %d\n", b.get().bagname.c_str(), c);
            count += c;
        }

        // total += b.get().count;
        // printf("count %d\n", count);
        // count += (childcount * b.get().count);
    }
    printf("count: %d\n", count);

    return count;
}

int main()
{
    std::map<std::string, struct Bag> bagmap;

    for (std::string line; std::getline(std::cin, line) && !line.empty();) {
        auto found = line.find(" bags contain");
        if (found != std::string::npos) {
            std::string bagname = line.substr(0, found);

            // check if in map already
            if (!bagmap.count(bagname))
                bagmap.insert({bagname, Bag(bagname)});

            auto &bag = bagmap[bagname];

            if (line.find("no other") != std::string::npos) {
                printf("%s : skipping now\n", line.c_str());
                continue;
            }
            line = line.substr(found + sizeof(" bags contain"));

            auto next = line.find(" bag");
            while (next != std::string::npos){
                printf("\n line %s\n", line.c_str());
                int count = line[0] - '0';
                printf("\n count %d\n", count);

                auto childbagname = line.substr(2, next-2);

                if (!bagmap.count(childbagname))
                    bagmap.insert({childbagname, Bag(childbagname)});

                auto &childbag = bagmap[childbagname];
                // counts aren't unique like bag name..
                // childbag.count = count;

                printf("line2: %s, count: %d, childbag: %s\n", line.c_str(), count, childbag.bagname.c_str());

                childbag.parentBags.push_back(bag); // keep a reference to parent bag.

                bag.childBags.push_back({count, childbag});
                if (line.find("shiny gold") != std::string::npos) {
                    bag.containsGold = true;
                }

                try {
                    line = line.substr(next + sizeof(" bag"));
                    auto f = line.find(" ");
                    line = line.substr(f+1);
                } catch (std::out_of_range &e) {
                    printf("end of line: %s\n", line.c_str());
                    break;
                }
                next = line.find(" bag");
            }
        }
    }

    // walk upwards from the goldbag.
    auto &goldbag = bagmap["shiny gold"];
    recurse(goldbag.parentBags);

    int gold = 0;
    for (auto &[k,v] : bagmap) {
        if (v.containsGold) {
            printf("bag contains gold: %s\n", v.bagname.c_str());
            gold++;
        }
    }
    printf("part 1: %d\n", gold);

    for (auto &[k,v] : bagmap) {
        sleep(0.1);
        printf("bag: %s\n", k.c_str());
        printf("\tchilds:\n");
        for (auto &[c,b] : v.childBags)
            printf("\t\t%d %s\n", c, b.get().bagname.c_str());

        printf("\tparents:\n");
        for (auto c : v.parentBags)
            printf("\t\t%d %s\n", c.get().count, c.get().bagname.c_str());
        sleep(0.1);
    }


    // walk down from the goldbag.
    int count = delve(goldbag.childBags);

    printf("part 2: %d\n", count);

}
