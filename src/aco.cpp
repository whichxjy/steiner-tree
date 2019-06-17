#include "aco.hpp"
#include "dijkstra.hpp"
#include "common.hpp"
#include "ant.hpp"
#include "mst.hpp"
#include <algorithm>

namespace ACO {
    // Init value of each pheromone
    constexpr int PHM_INIT = 1;
    // The index of target node in terminals
    constexpr int TARGET_NODE_INDEX_IN_TERM = 0;
    // How many bad results you can endure?
    constexpr int BAD_ENDURE_TIMES = 20;
    // Pheromone attenuation coefficient in (0, 1)
    constexpr double PHM_ATTE_COE = 0.1;
}

// Ant Colony Optimization
int ACO::AntColonyAlgo(const std::vector<std::vector<int>>& graph, const std::vector<int>& terminals) {
    // The number of all nodes
    int V = graph.size();
    // [Initialize pheromone of each edge]
    std::vector<std::vector<double>> phm(V, std::vector<double>(V, PHM_INIT));
    // [Choose one of the terminals as the target node]
    int target_node = terminals[TARGET_NODE_INDEX_IN_TERM];
    // [Initialize each node's minimum distance from target node]
    std::vector<int> dist = Dijkstra(graph, target_node);
    // Minimun cost
    int min_cost = INF;
    // Bad result counter
    int bad_count = 0;
    // Continue Loop until there are too many bad results
    while (bad_count <= BAD_ENDURE_TIMES) {
        // If there are T terminals, then create (T - 1) ants
        std::vector<Ant> ants;
        for (int i = 0; i < terminals.size(); i++) {
            if (i != TARGET_NODE_INDEX_IN_TERM) {
                ants.emplace_back(terminals[i], target_node, graph, phm, dist);
            }
        }
        // [Geneate path for each ant]
        // How many ants haven't arrived in target node?
        int not_arrived_count = ants.size();
        // Continue loop until all ants arrived in the target node
        while (not_arrived_count > 0) {
            for (Ant& ant : ants) {
                if (!ant.arrived()) {
                    // [The ant will move to the next node]
                    ant.move();
                    // [Check if the ant arrived]
                    if (ant.arrived()) {
                        not_arrived_count -= 1;
                    }
                }
            }
        }
        // [Merge visited nodes of each ant]
        std::set<int> merge_set;
        for (const Ant& ant : ants) {
            merge_set.insert(ant.visited_set.begin(), ant.visited_set.end());
        }
        // [Create MST according to merge_set]
        std::vector<int> merge_nodes(merge_set.begin(), merge_set.end());
        MstResult mst_result = MST(graph, merge_nodes, target_node);
        // [Update the pheromone of each edge]
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                // Pheromone attenuation
                phm[i][j] *= (1 - PHM_ATTE_COE);
            }
        }
        // If edge(i, j) is in the MST path, then add pheromone to it.
        // parent[i]: parent of merge_nodes[i]
        if (mst_result.cost != INF) {
            const std::vector<int>& parent = mst_result.parent;
            for (int i = 0; i < merge_nodes.size(); i++) {
                // If merge_nodes[i] is not the target_node, then there's a path from merge_nodes[i] to parent[i].
                if (parent[i] != -1) {
                    // Add pheromone to this edge with (1 / Q).
                    // (1) In the global update, Q is the global optimal solution.
                    // (2) In the local update, Q is the solution of current iteration.
                    // Here is the latter.
                    phm[merge_nodes[i]][parent[i]] += (1.0 / mst_result.cost);
                }
            }
        }
        // [Check whether the result is good or not]
        if (mst_result.cost < min_cost) {
            // It's a good result
            min_cost = mst_result.cost;
            bad_count = 0;
        }
        else {
            // It's a bad result
            bad_count += 1;
        }
    }
    return min_cost;
}
