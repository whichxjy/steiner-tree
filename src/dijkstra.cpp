#include "dijkstra.hpp"
#include "common.hpp"
#include <functional>
#include <queue>

// Dijkstra's shortest path algorithm (start from nodes[start])
std::vector<int> ACO::Dijkstra(const std::vector<std::vector<int>>& graph, int start) {
    // The number of nodes
    int V = graph.size();
    // found[i] will be true if nodes[i] is included in shortest path tree
    std::vector<bool> found(V, false);
    // dist[i] will hold the shortest distance from nodes[start] to nodes[i]
    std::vector<int> dist(V, INF);

    // dist[node] & node
    using iPair = std::pair<int, int>;
    // Priority for dist[node] & node
    std::priority_queue<iPair, std::vector<iPair>, std::greater<iPair>> pq;

    // Start from nodes[start]
    dist[start] = 0;
    pq.emplace(dist[start], start);
    
    while (!pq.empty()) {
        // nodes[curr] has the minimum distance
        int curr = pq.top().second;
        pq.pop();

        found[curr] = true;

        for (int w = 0; w < V; w++) {
            // Get successors
            if (!found[w] && graph[curr][w] != 0 && dist[curr] + graph[curr][w] < dist[w]) {
                // nodes[w] is not found and can be reached from curr
                dist[w] = dist[curr] + graph[curr][w];
                pq.emplace(dist[w], w);
            }
        }
    }

    return dist;
}