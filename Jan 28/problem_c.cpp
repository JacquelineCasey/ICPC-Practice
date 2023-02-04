
#include <iostream>
#include <unordered_map>
#include <vector>

#define int long long

auto main() -> decltype(1) {
    std::unordered_map<int, int> problem_classes {};

    int n;
    int k;

    std::cin >> n >> k;

    for (int i {0}; i < n; i++) {
        int item;
        std::cin >> item;

        if (problem_classes.find(item) != problem_classes.end()) {
            problem_classes[item]++;
        }
        else {
            problem_classes[item] = 1;
        }
        
    }

    std::vector<int> classes {};
    for (auto [key, value] : problem_classes) {
        classes.push_back(value);
    }  

    int c {static_cast<int>(classes.size())};

    int P {998244353l};

    std::vector<std::vector<int>> DP (k+1, std::vector<int>(c, 0));

    // if (k > c) {
    //     std::cout << 0 << '\n';
    //     return 0;
    // }

    for (int i {0}; i < k+1; i++) {
        for (int j {0}; j < c; j++) {
            if (i == 0) {
                DP[i][j] = 1;
                // std::cout << "i:" << i << " j:" << j << " -> " << DP[i][j] << '\n';
                continue;
            } 
            if (i > j + 1) {
                DP[i][j] = 0;
                // std::cout << "i:" << i << " j:" << j << " -> " << DP[i][j] << '\n';
                continue;
            }
            if (i == 1 && j == 0) {
                DP[i][j] = classes.at(j) % P;
                // std::cout << "i:" << i << " j:" << j << " -> " << DP[i][j] << '\n';
                continue;
            }

            int result {0};
            result += classes[j] * DP.at(i-1).at(j-1);
            // std::cout << result << '\n';
            result += DP.at(i).at(j-1);

            DP[i][j] = result % P;
            // std::cout << "i:" << i << " j:" << j << " -> " << DP[i][j] << '\n';
        }
    }

    std::cout << DP[k][c - 1] << '\n';
}
