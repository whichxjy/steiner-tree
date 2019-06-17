#ifndef _MST_HPP_
#define _MST_HPP_

#include <vector>

namespace GA {
    // Minimum Spanning Tree
    int MST(const std::vector<std::vector<int>>& graph, const std::vector<int>& nodes);
}

namespace ACO {
    // Result of MST
    struct MstResult {
        int cost;
        std::vector<int> parent;

        // Constructor
        MstResult() = default;
        MstResult(int cost, const std::vector<int>& parent);
    };

    // Minimum Spanning Tree
    MstResult MST(const std::vector<std::vector<int>>& graph, const std::vector<int>& nodes, int start_node);
}

#endif // !_MST_HPP_
