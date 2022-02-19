

#include <iostream>
#include <array>
#include <vector>

void display_sequence(const std::vector<int>& vec) {
    std::string list {""};

    for (int i : vec) {
        list += std::to_string(i);
        if (i != vec[vec.size()-1])
            list += ' ';
    }
        
    std::string range {""};
    range += std::to_string(vec[0]);
    range += "-";
    range += std::to_string(vec[vec.size() - 1]);

    if (range.length() < list.length())
        std::cout << range;
    else {
        std::cout << list;
    }
} 

int main() {
    std::array<bool, 1002> arr {};

    int n {};
    std::cin >> n;

    for (int i {0}; i < n; i++) {
        int stop {};
        std::cin >> stop;

        arr[stop] = true;
    }

    std::vector<int> vec {};
    for (int i {1}; i <= 1001; i++) {
        if (arr[i]) {
            vec.push_back(i);
        }
        else {
            if (vec.size() > 0) {
                display_sequence(vec);
                std::cout << ' ';
            }
            vec = {};
        }
    }

    std::cout << '\n';

    return 0;
}