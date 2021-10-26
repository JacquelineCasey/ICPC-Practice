
#include <iostream>

struct Rational {
    int num = -42;
    int denom = 1;
};

// long double is 16 bytes on my machine, more than enough.
Rational get_approximation(int max_denominator, long double real) {
    return {0, 0};
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
