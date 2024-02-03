
/* Problem: Given a digraph weighted graph with vertices {0, ..., N-1}, 
 * determine the maximum flow from node 0 to N-1. 
 *
 * We want the value, but it should also be possible to recover the flow itself.
 * 
 * Input: N M on one line, followed by triples on next M lines (u, v, w) representing
 * an edge u -> v with positive integer weight w. */

/* 1.in graph given by https://www.geeksforgeeks.org/max-flow-problem-introduction, 
 * has max flow = 23 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

/* (G: graph) will mean G[u] holds all of u's neighbors, so that G[u][v] exists if
 * v is a neighbor, and the value will be the weight. */
using graph = std::vector<std::unordered_map<int, int>>;

/* Returns a path from source to target, and gives the minimum edge weight along
 * that path. The path needs to be reversed at the end. */
int DFS(const graph& G, int source, int target, std::vector<int>& path, std::unordered_set<int>& visited) {
    if (visited.contains(source)) {
        return -1;
    }
    visited.insert(source);
    if (source == target) {
        path.push_back(source);
        return 1'000'000'000;  // ~infinity
    }
    for (auto [v, w] : G[source]) {
        if (w > 0) {
            int result = DFS(G, v, target, path, visited);
            if (result > 0) {
                path.push_back(source);

                return std::min(result, w);
            }
        }
    }
    return -1;
}

/* O(f * E), where f is the max flow, assuming integer edge weights. */
std::pair<int, graph> ford_fulkerson(const graph& G, int source, int sink) {
    int n  {static_cast<int>(G.size())};
    graph flow_graph (n, std::unordered_map<int, int> {});
    graph residual_graph (n, std::unordered_map<int, int> {});
    for (int u {0}; u < n; u++) {
        for (auto [v, w] : G[u]) {
            flow_graph[u][v] = 0;
            residual_graph[u][v] = w;
            if (!residual_graph[v].contains(u)) {
                residual_graph[v][u] = 0;
            }
        }
    }
    int flow {0};
    while (true) {
        std::vector<int> path {};
        std::unordered_set<int> visited {};
        int pushed_flow = DFS(residual_graph, source, sink, path, visited);
        if (pushed_flow <= 0) {
            break;
        }
        flow += pushed_flow;
        path.pop_back();  // That's the start node, which we know. 
        std::reverse(path.begin(), path.end()); 
        int u = source;
        for (int v : path) {
            int unapplied_flow = pushed_flow;
            if (flow_graph[v].contains(u)) {
                flow_graph[v][u] -= unapplied_flow;
                if (flow_graph[v][u] >= 0) {
                    unapplied_flow = 0;
                }
                else {
                    unapplied_flow = -flow_graph[v][u];
                    flow_graph[v][u] = 0;
                }
            }
            if (flow_graph[u].contains(v)) {
                flow_graph[u][v] += unapplied_flow;
            }
            residual_graph[u][v] -= pushed_flow;
            residual_graph[v][u] += pushed_flow;
            u = v;
        }
    }
    return {flow, flow_graph};
}

int main() {
    int n {};
    int m {};
    std::cin >> n >> m;
    graph G {};
    for (int i {0}; i < n; i++) {
        G.push_back({});
    }
    for (int i {0}; i < m; i++) {
        int u {};
        int v {};
        int w {};
        std::cin >> u >> v >> w;

        G[u][v] = w;
    }
    auto [f, flow_graph] = ford_fulkerson(G, 0, n-1);
    std::cout << f << '\n';
}
