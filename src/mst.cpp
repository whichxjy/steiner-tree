#include "mst.hpp"
#include "common.hpp"
#include <queue>
#include <functional>
#include <utility>

// Minimum Spanning Tree
int GA::MST(const std::vector<std::vector<int>>& graph, const std::vector<int>& nodes) {
    if (nodes.size() == 0) {
        return INF;
    }

    // The number of nodes
    int S = nodes.size();
    // Construct a MST for nodes[0], nodes[1], ... nodes[S - 1]
    std::vector<int> parent(S, -1);
    // Key values used to pick minimum weight edge in cut
    std::vector<int> key(S, INF);
    // Check if the node is in MST
    std::vector<bool> inMST(S, false);

    // key[node] & node
    using iPair = std::pair<int, int>;
    // Priority for key[node] & node
    std::priority_queue<iPair, std::vector<iPair>, std::greater<iPair>> pq;

    // Start from nodes[0]
    key[0] = 0;
    pq.emplace(key[0], 0);

    while (!pq.empty()) {
        // nodes[u] is the picked node with the least key
        int u = pq.top().second;
        pq.pop();

        // Put nodes[u] in MST
        inMST[u] = true;
        
        // Find adjacent of nodes[u]
        for (int i = 0; i < S; i++) {
            if (!inMST[i] && graph[nodes[u]][nodes[i]] > 0 && graph[nodes[u]][nodes[i]] < key[i]) {
                // Update the key of nodes[i]
                key[i] = graph[nodes[u]][nodes[i]];
                pq.emplace(key[i], i);
                parent[i] = u;
            }
        }
    }

    // Minimum cost of all selected edges
    int min_cost = 0;
    // Check if the root is already found (parent[root] = -1)
    bool root_found = false;
    for (int i = 0; i < S; i++) {
        if (parent[i] != -1) {
            // Add weight to sum cost with the weight of Edge(nodes[i], nodes[parent[i]])
            min_cost += graph[nodes[i]][nodes[parent[i]]];
        }
        else if (!root_found) {
            // If the root hadn't been found and parent[i] == -1, then nodes[i] is the root
            root_found = true;
        }
        else {
            // If the root was found and parent[i] == -1, then fail to construct a MST
            return INF;
        }
    }

    return min_cost;
}

// Constructor
ACO::MstResult::MstResult(int cost, const std::vector<int>& parent) : cost(cost), parent(parent) {
    // Empty
}

// Minimum Spanning Tree
ACO::MstResult ACO::MST(const std::vector<std::vector<int>>& graph, const std::vector<int>& nodes, int start_node) {
    if (nodes.size() == 0) {
        return { INF, std::vector<int>() };
    }

    // The number of nodes
    int S = nodes.size();
    // parent[i] will hold the previous nodes[i]
    std::vector<int> parent(S, -1);
    // Key values used to pick minimum weight edge in cut
    std::vector<int> key(S, INF);
    // Check if the node is in MST
    std::vector<bool> inMST(S, false);

    // key[node] & node
    using iPair = std::pair<int, int>;
    // Priority for key[node] & node
    std::priority_queue<iPair, std::vector<iPair>, std::greater<iPair>> pq;

    // Construct a MST for nodes[0], nodes[1], ... nodes[S - 1]
    // [Start from start_node]
    for (int i = 0; i < S; i++) {
        if (nodes[i] == start_node) {
            key[i] = 0;
            pq.emplace(key[i], i);
            break;
        }
    }

    while (!pq.empty()) {
        // nodes[u] is the picked node with the least key
        int u = pq.top().second;
        pq.pop();

        // Put nodes[u] in MST
        inMST[u] = true;

        // Find adjacent of nodes[u]
        for (int i = 0; i < S; i++) {
            if (!inMST[i] && graph[nodes[u]][nodes[i]] > 0 && graph[nodes[u]][nodes[i]] < key[i]) {
                // Update the key of nodes[i]
                key[i] = graph[nodes[u]][nodes[i]];
                pq.emplace(key[i], i);
                parent[i] = u;
            }
        }
    }

    // Minimum cost of all selected edges
    int min_cost = 0;
    // Check if the root is already found (parent[root] = -1)
    bool root_found = false;
    for (int i = 0; i < S; i++) {
        if (parent[i] != -1) {
            // Add weight to sum cost with the weight of Edge(nodes[i], nodes[parent[i]])
            min_cost += graph[nodes[i]][nodes[parent[i]]];
        }
        else if (!root_found) {
            // If the root hadn't been found and parent[i] == -1, then nodes[i] is the root
            root_found = true;
        }
        else {
            // If the root was found and parent[i] == -1, then fail to construct a MST
            return { INF, std::vector<int>() };
        }
    }

    return { min_cost, parent };
}