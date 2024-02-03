
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

/* Computes a path and the minimum edge weight along that path. */
std::pair<int, std::vector<int>> BFS(const graph& G, int source, int target) {
    std::vector<int> front {source};
    std::unordered_map<int, int> back{};
    back[source] = -1;

    while (!back.contains(target)) {
        std::vector<int> next_front {};

        for (int u : front) {
            for (auto [v, w] : G[u]) {
                if (w > 0) {
                    if (!back.contains(v)) {
                        back[v] = u;
                        next_front.push_back(v);
                    }
                }
            } 
        }

        front = next_front;

        if (front.size() == 0) {
            return {-1, {}};
        }
    }

    std::vector<int> path;

    int u = target;
    int result = 1'000'000'000;  // ~infinity
    while (u != source) {
        result = std::min(G[back[u]].at(u), result);
        
        path.push_back(u);
        u = back[u];
    }
    
    std::reverse(path.begin(), path.end());
    return {result, path};
}

// O(V E^2), but also O(E f) (whichever is better). Probably a bit slower in
// the O(E f) case?
std::pair<int, graph> edmonds_karp(const graph& G, int source, int sink) {
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
        auto [pushed_flow, path] = BFS(residual_graph, source, sink);  // !
        if (pushed_flow <= 0) {                                        // !
            break;                                                     // !
        }                                                              // !
        flow += pushed_flow;
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
    auto [f, flow_graph] = edmonds_karp(G, 0, n-1);
    std::cout << f << '\n';

    for (int u {0}; u < n; u++) {
        for (auto [v, w] : flow_graph[u]) {
            if (w > 0) {
                std::cout << u << " -> " << v << ": " << w << '\n';
            }
        }
    }
}
