
#include <iostream>
#include <vector>
#include <queue>

struct Graph {
    std::vector<std::vector<int>> adj {};

    std::vector<int> level {};
    std::vector<bool> visited {};
};


void compute_level(Graph& G) {
    std::queue<int> queue {};

    queue.push(1);
    while (!queue.empty()) {
        int v = queue.front();
        queue.pop();
        G.visited[v] = true;
        for (int u : G.adj[v]) {
            if (!G.visited[u]) {
                // std::cout << v << " -> " << u << '\n';
                queue.push(u);
                G.level[u] = std::min(G.level[u], G.level[v] + 1);
            }
        }
    }
}


int main() {
    int n {};
    int m {};

    std::cin >> n >> m;

    Graph G {};
    G.adj = std::vector(n+1, std::vector<int> {}); // We will care only about 1...n
    G.level = std::vector(n+1, 1000000);
    G.visited = std::vector(n+1, false);
    G.level[0] = -100000;
    G.level[1] = 0;
    

    for (int i {0}; i < m; i++) {
        int v1 {};
        int v2 {};

        std::cin >> v1 >> v2;

        G.adj[v1].push_back(v2);
        G.adj[v2].push_back(v1);
    }

    compute_level(G);

    std::cout << G.level[n] - 1 << '\n';
}
