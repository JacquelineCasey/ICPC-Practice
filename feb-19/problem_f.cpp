
#include <iostream>
#include <array>
#include <vector>

int main() {
    int n {};
    std::cin >> n;

    std::vector<int> weights {};
    for (int i {0}; i < n; i++) {
        int w {};
        std::cin >> w;

        weights.push_back(w);
    }

    long long weight_all_baskets {0};

    long long num_permutations = 1;
    for (int i {0}; i < n; i++) {
        num_permutations *= 2;
    }

    for (int w : weights) {
        weight_all_baskets += w * num_permutations / 2; // Each fruit is only included in half of the baskets.
    }

    /* Now count all baskets under 200 grams, and subtract their weight. We pick up to 3
     * fruits*/

    for (int a {0}; a < n; a++) {
        if (weights[a] < 200) {
            weight_all_baskets -= weights[a]; // These are the 1 item baskets.

            for (int b {a + 1}; b < n; b++) {
                if (weights[a] + weights[b] < 200) {
                    weight_all_baskets -= weights[a] + weights[b]; // These are the 2 item baskets.

                    for (int c {b + 1}; c < n; c++) {
                        if (weights[a] + weights[b] + weights[c] < 200) {
                            weight_all_baskets -= weights[a] + weights[b] + weights[c]; // These are the 3 item baskets.

                            // Note that all 4 item baskets are always > 200 g, so we never need to subtract them.
                        }
                    }
                }
            }
        }
    }

    std::cout << weight_all_baskets << '\n';

    return 0;
}