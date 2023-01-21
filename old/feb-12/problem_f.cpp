
#include <array>
#include <iostream>
#include <set>
#include <utility>

/* Surprisingly, this question was a bit of a mess. I decided to take an approach
 * that sinks the island to various levels to see which islands remain. We throw
 * answers into a set to prevent duplicates. */

int count_islands(const std::array<int, 12>& arr) {
    std::set<std::pair<int, int>> islands {};

    for (int i {0}; i < 12; i++) {
        bool flag {false};
        int left {0};
        for (int j {0}; j < 12; j++) {
            if (arr[j] > arr[i]) {
                if (!flag)
                    left = j;
                flag = true;
            }
            else if (flag) {
                flag = false;
                islands.insert(std::pair(left, j));
            }
        }
    }

    // for (auto [a, b] : islands) {
    //     // std::cout << a << ' ' << b << "|\n";
    // }

    return islands.size();
}

int main() {
    int k {};
    std::cin >> k;

    for (int i {0}; i < k; i++) {
        int num {};
        std::cin >> num;

        std::array<int, 12> arr {};
        for (int i {0}; i < 12; i++) {
            std::cin >> arr[i];
        }

        std::cout << num << " " << count_islands(arr) << '\n';
    }

    


    return 0;
}