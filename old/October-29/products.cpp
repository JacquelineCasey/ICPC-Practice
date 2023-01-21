
#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n {};
    std::cin >> n;
    std::vector<long long> A(n, 0);

    for (int i {}; i < n; i++) {
        std::cin >> A[i];
    }

    /* Replace with 1 and -1 and 0 */
    for (long long& a : A) {
        if (a >= 1) {
            a = 1;
        }
        if (a <= -1) {
            a = -1;
        }
    }

    std::vector<long long> negative_prods(n, 0);
    std::vector<long long> positive_prods(n, 0);
    std::vector<long long> zero_prods(n, 0);

    // Calculate base case
    if (A[n-1] < 0) {
        negative_prods[n-1] = 1;
    }
    else if (A[n-1] > 0) {
        positive_prods[n-1] = 1;
    }
    else {
        zero_prods[n-1] = 1;
    }

    for (int i {n-2}; i >= 0; i--) {
        // split on sign of A[i]
        if (A[i] == 0) {
            negative_prods[i] = 0;
            positive_prods[i] = 0;
            zero_prods[i] = n - i;
        }
        else if (A[i] > 0) {
            negative_prods[i] = negative_prods[i+1];
            positive_prods[i] = positive_prods[i+1] + 1;
            zero_prods[i] = zero_prods[i+1];
        }
        else {
            negative_prods[i] = positive_prods[i+1] + 1;
            positive_prods[i] = negative_prods[i+1];
            zero_prods[i] = zero_prods[i+1];
        }
    }

    long long zeros {};
    long long positives {};
    long long negatives {};

    for (int i {0}; i < n; i++) {
        zeros += zero_prods[i];
        positives += positive_prods[i];
        negatives += negative_prods[i];
        // std::cout << "(" << negative_prods[i] << ", " << positive_prods[i] << ", " << zero_prods[i] << ")\n";
    }


    // for (int l {0}; l < n; l++) {
    //     long long prod {1};
    //     for (int i = l; i < n; i++) {
    //         prod *= A[i];
    //         if (prod == 1) {
    //             positives++;
    //         }
    //         else if (prod == -1) {
    //             negatives++;
    //         }
    //         else {
    //             zeros++;
    //         }
    //     }
    // }

    std::cout << negatives << " " << zeros << " " << positives << '\n';
}