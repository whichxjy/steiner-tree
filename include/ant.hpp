#ifndef _ANT_HPP_
#define _ANT_HPP_

#include <vector>
#include <set>
#include <queue>
#include <utility>

namespace ACO {
    struct Ant {
        // Current node
        int curr_node;
        // Target node
        int target_node;
        // The entire graph
        const std::vector<std::vector<int>>& graph;
        // Pheromone of each edge
        const std::vector<std::vector<double>>& phm;
        // Each node's minimum distance from target node
        const std::vector<int>& dist;
        // Has this node been visited?
        std::vector<bool> visited;
        // Store all the nodes that had been visited
        std::set<int> visited_set;
        // Priority queue for all the nodes that had been visited (pair: dist[node] & node)
        std::priority_queue<std::pair<int, int>> visited_pq;

        // Constructor
        Ant() = default;
        Ant(int curr_node, int target_node, const std::vector<std::vector<int>>& graph,
            const std::vector<std::vector<double>>& phm, const std::vector<int>& dist);

        // Move to the next node
        void move();

        // Relocate the current node
        void relocate();

        // Check if the ant arrived the target node
        bool arrived() const;
    };
}

#endif // !_ANT_HPP_
