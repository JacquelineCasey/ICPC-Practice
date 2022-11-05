// https://open.kattis.com/contests/w7tjw3/problems/maximumsubarrays


#include <iostream>
#include <vector>



int main() {
    int n;
    int k;
    std::cin >> n >> k;


    std::vector<std::vector<long long>> DP (k+1, std::vector<long long>(n, 0));
    std::vector<long long> A (n, 0);

    // std::vector<long long> left_to_right (n, 0);
    // std::vector<long long> right_to_left (n, 0);


    for (int i {}; i < n; i++)
        std::cin >> A[i];

    for (int k_curr {1}; k_curr <= k; k_curr ++) {
        for (int j {0}; j < n; j++) {
            long long max {-1000000000};
            long long sum {0};
            for (int i {j}; i >= 0; i--) {
                // std::cout << sum << '\n';
                sum += A[i];
                if (k_curr != 1 && i != 0) {
                    max = std::max(sum + DP[k_curr -1][i - 1], max);
                }
                else if (k_curr == 1) {
                    max = std::max(max, sum);
                }
                // std::cout << max << '\n';
            }       

            if (j != 0) {
                max = std::max(max, DP[k_curr][j - 1]);
            }

            // std::cout << "DP[" << k_curr << "][" << j << "] = " << max << "\n";
            DP[k_curr][j] = max;

        }
    }

    std::cout << DP[k][n-1] << '\n';
}
