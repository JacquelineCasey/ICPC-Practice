
#include <iostream>
#include <vector>

bool check_query(const std::vector<int>& clusters, int query) {
    int left {0}; // [)
    int right {static_cast<int>(clusters.size())}; // past the end. [)

    int sum {0};

    /* First, run right and build up sum */
    while (sum < query) {
        if (left == static_cast<int>(clusters.size()))
            return false;
        sum += clusters[left];
        left++;
    }

    /* Now we work leftwards, but the left pointer chases us if necessary. */
    while (left >= 0) {
        if (sum == query)
            return true;

        left--;
        if (left <= -1)
            return false;
        sum -= clusters[left];

        /* Now compensate with the right pointer. */
        while (sum < query) {
            right--;
            if (right < left)
                return false;
            sum += clusters[right];
        }
    }

    return false;
}

int main() {
    int m {};
    int n {};
    std::vector<int> clusters {};
    std::cin >> m >> n;

    for (int i {0}; i < m; i++) {
        int temp {};
        std::cin >> temp;
        clusters.push_back(temp);
    }

    for (int i {0}; i < n; i++) {
        int query {};
        std::cin >> query;

        if (check_query(clusters, query))
            std::cout << "Yes\n";
        else
            std::cout << "No\n";
    }

    return 0;
}