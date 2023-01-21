// https://open.kattis.com/contests/w7tjw3/problems/maximumsubarrays


#include <iostream>
#include <vector>
#include <climits>



int main() {
    int n;
    int k;
    std::cin >> n >> k;


    std::vector<std::vector<long long>> DP (k+1, std::vector<long long>(n, 0));
    std::vector<long long> A (n, 0);


    std::vector<int> start_indices (n, 0);

    for (int i {}; i < n; i++)
        std::cin >> A[i];

    for (int k_curr {1}; k_curr <= k; k_curr ++) {
        for (int j {0}; j < n; j++) {
            /* Compute DP[k_curr][j] */

            long long max {LLONG_MIN / 2}; // Basically -infinity. Needs to not overflow.
            long long sum {0};

            if (j > 0 && start_indices[j-1] > start_indices[j]) {
                start_indices[j] = start_indices[j-1];
            }

            int stop = start_indices[j];
            int new_stop = j;
            for (int i {j}; i >= stop; i--) {
                sum += A[i];
                if (k_curr != 1 && i != 0) {
                    if (sum + DP[k_curr -1][i - 1] >= max) {
                        max = sum + DP[k_curr -1][i - 1];
                        new_stop = i;
                    }
                }
                else if (k_curr == 1) {
                    max = std::max(max, sum);
                    new_stop = 0;
                }
            }

            start_indices[j] = new_stop;


            if (j != 0) {
                max = std::max(max, DP[k_curr][j - 1]);
            }

            // std::cout << "DP[" << k_curr << "][" << j << "] = " << max << '\n';
            // std::cout << new_stop << '\n';
            DP[k_curr][j] = max;
        }
    }

    std::cout << DP[k][n-1] << '\n';
}
