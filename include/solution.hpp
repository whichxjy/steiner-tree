#ifndef _SOLUTION_HPP_
#define _SOLUTION_HPP_

#include <vector>
#include <memory>

namespace GA {
    struct Solution {
        // The entire graph
        const std::vector<std::vector<int>>& graph;
        // If chose[i] is chose to create a MST
        std::vector<bool> chose;
        // All the nodes had been chose
        std::vector<int> chose_nodes;
        // The sum of the distance of each edge in the MST
        int cost;

        // Constructor
        Solution() = default;
        Solution(const std::vector<std::vector<int>>& graph, const std::vector<bool>& chose);

        // When the chose[] changed, update solution for the new MST
        void update();
    };

    // Alias for pointer to solution
    using solution_ptr = std::shared_ptr<Solution>;

    // Compare function for pointer to solution
    bool operator<(solution_ptr lhs, solution_ptr rhs);
    bool operator==(solution_ptr lhs, solution_ptr rhs);
    bool operator>(solution_ptr lhs, solution_ptr rhs);

    // Create a random solution
    solution_ptr get_random_solution(const std::vector<std::vector<int>>& graph);

    // Create a solution for the MST of the entire graph
    solution_ptr get_full_solution(const std::vector<std::vector<int>>& graph);
}

#endif // !_SOLUTION_HPP_
