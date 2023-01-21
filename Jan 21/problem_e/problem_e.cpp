
#include <iostream>
#include <array>

int main() {
    std::string s {};
    std::cin >> s;

    std::array<long long, 26> counts {};

    for (char ch : s) {
        counts[ch - 'a']++;
    }

    long long p = 11092019;
    long long prod = 1;
    for (long long item : counts) {
        prod *= (item + 1);
        prod %= p;
    }

    std::cout << prod << '\n';
}

