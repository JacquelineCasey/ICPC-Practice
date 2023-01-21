/* https://open.kattis.com/contests/nar21practice3/problems/countingclauses */

#include <iostream>

int main() {
    int a {};

    std::cin >> a;

    if (a >= 8)
        std::cout << "satisfactory\n"; 

    else
        std::cout << "unsatisfactory\n"; 

    return 0;
}