/* https://open.kattis.com/contests/nar21practice3/problems/fishmongers */

#include <iostream>
#include <vector>
#include <algorithm>

struct Monger {
    long fish_to_buy {};
    long price_per_pound {};
};

// compare by price.
bool operator<(const Monger& lhs, const Monger& rhs) {
    return lhs.price_per_pound < rhs.price_per_pound; 
}

int main() {
    /* Input parsing. */
    int num_fish {};
    std::cin >> num_fish;

    int num_mongers {};
    std::cin >> num_mongers;

    std::vector<long> fish_sizes {};
    for (int i {}; i < num_fish; i++) {
        long fish_size {};
        std::cin >> fish_size;

        fish_sizes.push_back(fish_size);
    }

    std::vector<Monger> mongers {};
    for (int i {}; i < num_mongers; i++) {
        int fish_count {};
        int price_per_pound {};

        std::cin >> fish_count >> price_per_pound;

        mongers.push_back({fish_count, price_per_pound});
    }

    /* Now we sort Fish (backwards, so largest to smallest)*/
    std::sort(fish_sizes.rbegin(), fish_sizes.rend());

    /* Now sort mongers (backwards by price per kilo, so ascending) */
    std::sort(mongers.rbegin(), mongers.rend());

    /* Now we simply give fish to each monger in order while we still have fish */

    int curr_monger {};
    long long profit {};
    for (int curr_fish_size : fish_sizes) {
        if (mongers[curr_monger].fish_to_buy == 0) 
            curr_monger++;

        if (curr_monger >= static_cast<int>(mongers.size()))
            break;

        profit += mongers[curr_monger].price_per_pound * curr_fish_size;
        mongers[curr_monger].fish_to_buy--;
    }

    std::cout << profit << std::endl;

    return 0;
}