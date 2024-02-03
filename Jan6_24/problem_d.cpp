
#include <iostream>
#include <vector>
#include <tuple>

#include <set>

bool all_even_degree(std::vector<std::set<int>>& graph) {
    for (auto& vec : graph) {
        if (vec.size() % 2 != 0) {
            return false;
        }
    }

    return true;
}

int main() {
    int n {};
    int m {};
    int k {};

    std::cin >> n >> m >> k;

    std::set<std::tuple<int, int>> original_edges {};
    std::set<std::tuple<int, int>> new_edges {};

    for (int i {0}; i < m; i++) {
        int a {};
        int b {};

        std::cin >> a >> b;

        if (a > b) {
            std::swap(a, b);
        }

        original_edges.insert({a, b});
    }

    for (int i {0}; i < k; i++) {
        int a {};
        int b {};

        std::cin >> a >> b;

        if (a > b) {
            std::swap(a, b);
        }

        new_edges.insert({a, b});
    }

    std::set<std::tuple<int, int>> change_set {};

    for (auto [u, v] : original_edges) {
        if (!new_edges.contains({u, v})) {
            change_set.insert({u, v});
        }
    }

    for (auto [u, v] : new_edges) {
        if (!original_edges.contains({u, v})) {
            change_set.insert({u, v});
        }
    }


    std::vector<std::set<int>> graph (n, std::set<int>());

    for (auto [i, j] : change_set) {
        graph[i - 1].insert(j - 1);
        graph[j - 1].insert(i - 1);
    }

    std::vector<std::tuple<int, int, int>> triples {};

    if (all_even_degree(graph)) {
        std::cout << "YES\n";

        for (int i {0}; i < n; i++) {
            while (graph[i].size() != 0) {
                int u = *graph[i].begin();
                graph[i].erase(u);

                int v = *graph[i].begin();
                graph[i].erase(v);

                graph[u].erase(i);
                graph[v].erase(i);

                if (graph[u].contains(v)) {
                    graph[u].erase(v);
                    graph[v].erase(u);
                }
                else {
                    graph[u].insert(v);
                    graph[v].insert(u);
                }  

                triples.push_back({i + 1, u + 1, v + 1});
                // std::cout << (i+1) << ' ' << (u + 1) << ' ' << (v + 1) << '\n';
            }
        }

        std::cout << triples.size() << '\n';
        for (auto [a, b, c] : triples) {
            std::cout << a << ' ' << b << ' ' << c << '\n';
        }
    }
    else {
        std::cout << "NO\n";
    }
}
