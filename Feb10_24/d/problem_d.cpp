
#include <iostream>
#include <vector>

int main() {
    int n {};
    int k {};

    std::cin >> n >> k;

    std::vector<int> throws {};

    for (int i {0}; i < k; i++) {
        std::string word {};
        std::cin >> word;
        // std::cout << "READ: " << word << '\n';

        if (word == "undo") {
            int amount {};
            std::cin >> amount;

            for (int j {0}; j < amount; j++) {
                throws.pop_back();
            }
        } 
        else {
            // std::cout << "HERE: " << word << '\n';
            int amount = std::stoi(word);
            throws.push_back(amount);
        }
    }

    /* Now execute the actual commands. */
    int total {};

    for (int toss : throws) {
        total += toss;
        total = ((total % n) + n) % n;  // Prevent C negative remainder shenanigans
    }

    std::cout << total << '\n';
}
