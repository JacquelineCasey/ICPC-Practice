
#include <iostream>

struct Rational {
    int num = -42;
    int denom = 1;
};

// long double is 16 bytes on my machine, more than enough.
Rational get_approximation(int max_denominator, long double real) {
    /* Let's check a bunch of nearby values, and remember which one was the best.
     *
     * Start at 0/1
     * Keep track of least upper bound as we iterate over d: for LUB n/d, consider
     * n/d+1, n+1/d+1, and n+2/d+2. Update best approx if necessary. Update LUB.
     */

    int LUB_n = 0;
    int best_n {0};
    int best_d {1};
    long double best_error = real;

    for (int d {1}; d <= max_denominator; d++) {
        /* Generate error values for our three tests */
        long double err_1 = ((long double) (LUB_n)     / d) - real;
        long double err_2 = ((long double) (LUB_n + 1) / d) - real;
        long double err_3 = ((long double) (LUB_n + 2) / d) - real;

        /* Update best approximation if necessary */
        if (std::abs(err_1) < best_error) {
            best_n = LUB_n;
            best_d = d;
            best_error = std::abs(err_1);
        }
        if (std::abs(err_2) < best_error) {
            best_n = LUB_n + 1;
            best_d = d;
            best_error = std::abs(err_2);
        }
        if (std::abs(err_3) < best_error) {
            best_n = LUB_n + 2;
            best_d = d;
            best_error = std::abs(err_3);
        }

        /* Update LUB */
        LUB_n = (err_2 < 0) ? LUB_n + 1 : LUB_n;
    }

    return {best_n, best_d};
}

int main() {
    int n_trials {}; 
    std::cin >> n_trials;

    for (int i {0}; i < n_trials; i++) {
        int line {};
        int M {};
        long double real {};
        std::cin >> line >> M >> real;

        Rational approx = get_approximation(M, real);
        std::cout << line << ' ' << approx.num << '/' << approx.denom << '\n';
    }
    
    return 0;
}
