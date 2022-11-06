// https://open.kattis.com/contests/w7tjw3/problems/maximumsubarrays

/* This solution occurred to me after thinking about the problem for approximately
 * 1 minute the next day. */

#include <iostream>
#include <vector>
#include <climits>


int main() {
    int n;
    int k;
    std::cin >> n >> k;

    /* DP[k][i] represents the max k-subarray sum using A[0...i]. */
    std::vector<std::vector<long long>> DP (k+1, std::vector<long long>(n, 0));
    std::vector<long long> A (n, 0);


    std::vector<int> start_indices (n, 0);

    for (int i {}; i < n; i++)
        std::cin >> A[i];

    for (int k_curr {0}; k_curr <= k; k_curr ++) {
        
        /* For hacky reason, we interpret DP[k_curr] and DP[k_curr - 1] differently here.
         * DP[k_curr][i] requires its answer to use A[i]. DP[k_curr - 1][i] does not. 
         * After we computer DP[k_curr] completely, we update it in one pass to 
         * use the second interpretation.
         * 
         * Could this be done more clearly using seperate vectors... yes.
         * Did I do that... no. */

        for (int i {0}; i < n; i++) {
            /* Compute DP[k_curr][i] */

            if (k_curr == 0) {
                /* 0 subarrays have a sum of 0. */
                DP[k_curr][i] = 0;
                // std::cout << "DP[" << k_curr << "][" << i << "] = " << DP[k_curr][i] << '\n';
                continue;
            }

            if (i + 1 < k_curr) {
                /* Cannot fit, so answer is -inf. */
                DP[k_curr][i] = LLONG_MIN / 2;  // Basically -infinity. Needs to not overflow.
                // std::cout << "DP[" << k_curr << "][" << i << "] = " << DP[k_curr][i] << '\n';
                continue;
            }
        
            /* Option 1, add a new size one array at i. */
            long long res = LLONG_MIN / 2;  // -inf
            if (i > 0) {
                res = std::max(res, A[i] + DP[k_curr-1][i-1]);
            }
            else {
                res = std::max(res, A[i]);  // This is the last sum (k_curr == 1)
            }

            /* Option 2, extend an old array. */
            if (i > 0) {
                res = std::max(res, DP[k_curr][i-1] + A[i]);
            }
            else {
                /* There is no array to extend. */
            }

            DP[k_curr][i] = res;
            // std::cout << "DP[" << k_curr << "][" << i << "] = " << res << '\n';
        }

        /* STUPID HACK:
         *
         * We update the entire row to fit the new interpretation of DP[k]. 
         * DP[k][i] now represents the best sum ending anywhere to the right of i,
         * instead of ending exactly on i. */
        long long running_max = LLONG_MIN / 2;  // -inf
        for (int i {0}; i < n; i++) {
            running_max = std::max(running_max, DP[k_curr][i]);
            DP[k_curr][i] = running_max;
        }
    }

    /* This happens to be the max of the last row, after the stupid hack. */
    std::cout << DP[k][n-1] << '\n';
}
