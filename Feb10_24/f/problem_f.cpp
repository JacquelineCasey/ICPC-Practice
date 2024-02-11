
#include <iostream>
#include <vector>

using graph = std::vector<std::vector<int>>;

void dfs_make_tree(graph& G, std::vector<int>& parents, int parent, int v) {
    if (parents[v] != -1) {
        return;
    }

    parents[v] = parent;

    for (int u : G[v]) {
        dfs_make_tree(G, parents, v, u);
    }
}

void find_counts(graph& G, std::vector<int>& parents, std::vector<int>& counts, int node) {
    int count = 1;  // Always include the node itself.

    for (int child : G[node]) {
        if (child != parents[node]) { // Rule out the parent
            find_counts(G, parents, counts, child);

            count += counts[child];
        }
    }

    counts[node] = count;
}

std::vector<int> get_fragments(graph& G, std::vector<int>& parents, std::vector<int>& counts, int node, int n) {
    std::vector<int> fragments {};

    for (int child : G[node]) {
        if (child != parents[node]) {
            fragments.push_back(counts[child]);
        }
    }

    if (parents[node] != -2) {
        fragments.push_back(n - counts[node] + 1);
    }

    return fragments;
}

int main() {
    int n {};  // Number of edges!. Vertices is n + 1;
    std::cin >> n;

    // For comfort, we will store both copies of each edge.
    graph G (n + 1, std::vector<int>());

    for (int i {0}; i < n; i++) {
        int u {};
        int v {};

        std::cin >> u >> v;

        G[u].push_back(v);
        G[v].push_back(u);
    }
    
    /* -1 represents unvisited. -2 represents no parent (i.e. root) */
    std::vector<int> parents(n + 1, -1);

    dfs_make_tree(G, parents, -2, 0);

    std::vector<int> counts(n + 1, -1);

    find_counts(G, parents, counts, 0);

    int best_target = -1;
    int best_value = 0;

    for (int v {0}; v < n + 1; v++) {
        auto fragments = get_fragments(G, parents, counts, v, n);
        int cost = 0;

        for (int fragment : fragments) {
            cost += (n - fragment) * fragment;
        }

        cost /= 2;

        if (cost > best_value) {
            best_value = cost;
            best_target = v;
        }
    }

    auto fragments = get_fragments(G, parents, counts, best_target, n);

    std::sort(fragments.begin(), fragments.end());

    int a = fragments.at(fragments.size() - 1);
    int b = fragments.at(fragments.size() - 2);

    std::cout << best_value << ' ' << (best_value - a * b) << '\n';    
}
