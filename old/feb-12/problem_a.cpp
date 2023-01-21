
#include <array>
#include <iostream>
#include <set>
#include <utility>

/* As far as we know, this answer is correct, but it does not work fast enough.
 * This is a C++ adaptation of Jack Nugent's python, but the C++ speedup was not
 * enough to save us. */

void calc(int n, int d) {
    if (d > n) {
        std::cout << d << '/' << d-n;
        return;
    }

    int i = 0;
    while (d <= n) {
        n = n - d;
        i++;
    }

    int n_new = d;
    int d_new = d - n;
    n = n_new;
    d = d_new;

    for (int j {0}; j < i; j++) {
        d = n + d;
    }

    std::cout << n << '/' << d;
}

int main() {
    int k {};
    std::cin >> k;

    for (int i {0}; i < k; i++) {
        int n {};
        std::cin >> n;

        int num {};
        std::cin >> num;

        char slash {};
        std::cin >> slash;

        int denom {};
        std::cin >> denom;

        std::cout << n << " ";
        calc(num, denom); 
        std::cout << '\n';
    }

    


    return 0;
}