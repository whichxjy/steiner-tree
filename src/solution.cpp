#include "solution.hpp"
#include "mst.hpp"
#include "common.hpp"

// Constructor
GA::Solution::Solution(const std::vector<std::vector<int>>& graph, const std::vector<bool>& chose)
    : graph(graph), chose(chose) {
    // Update solution
    update();
}

// When the chose[] changed, update solution for the new MST
void GA::Solution::update() {
    // The number of all nodes
    int V = graph.size();
    // Update chose_nodes[]
    chose_nodes.clear();
    for (int i = 0; i < V; i++) {
        if (chose[i]) {
            chose_nodes.push_back(i);
        }
    }
    // Create MST and update the cost
    cost = MST(graph, chose_nodes);
}

// Compare function for pointer to solution
bool GA::operator<(solution_ptr lhs, solution_ptr rhs) {
    return lhs->cost < rhs->cost;
}

bool GA::operator==(solution_ptr lhs, solution_ptr rhs) {
    return lhs->cost == rhs->cost;
}

bool GA::operator>(solution_ptr lhs, solution_ptr rhs) {
    return lhs->cost > rhs->cost;
}

// Create a random solution
GA::solution_ptr GA::get_random_solution(const std::vector<std::vector<int>>& graph) {
    // The number of all nodes
    int V = graph.size();
    // Create random chose[]
    std::vector<bool> chose;
    for (int i = 0; i < V; i++) {
        chose.push_back(random_boolean());
    }
    // Create a solution according to the chose[]
    return std::make_shared<Solution>(graph, chose);
}

// Create a solution for the MST of the entire graph
GA::solution_ptr GA::get_full_solution(const std::vector<std::vector<int>>& graph) {
    // The number of all nodes
    int V = graph.size();
    // Create full chose[]
    std::vector<bool> chose(V, true);
    // Create a solution according to the chose[]
    return std::make_shared<Solution>(graph, chose);
}