
#include <algorithm>
#include <iostream>
#include <vector>

using modification = std::pair<int, char>;


int count_less_than(const std::vector<std::string>& strs, const std::string& search_str) {
    int left {0};
    int right {static_cast<int>(strs.size()) - 1};
    int n {static_cast<int>(strs.size())};

    while (true) {
        int mid {(left + right) / 2};
        if ((search_str > strs[mid]) && (mid + 1 >=  n || search_str <= strs[mid + 1])) {
            return mid + 1;
        }
        else if (search_str > strs[mid]) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
            if (right == -1)
                return 0;
        }
    }
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    int q;
    std::cin >> n >> q;

    std::string search_str {};
    std::cin >> search_str;

    std::vector<std::string> strs {};
    for (int i {0}; i < n; i++) {
        std::string str {};
        std::cin >> str;
        strs.push_back(str);
    }

    std::vector<modification> mods {};
    for (int i {0}; i < q; i++) {
        modification mod {};
        std::cin >> mod.first;
        std::cin >> mod.second;
        mods.push_back(mod);
    }

    std::sort(strs.begin(), strs.end());

    std::cout << count_less_than(strs, search_str) << '\n';
    for (auto [i, c] : mods) {
        for (int index {i - 1}; index < static_cast<int>(search_str.size()); index++) {
            search_str[index] = c;
        }
        std::cout << count_less_than(strs, search_str) << '\n';
    }
}