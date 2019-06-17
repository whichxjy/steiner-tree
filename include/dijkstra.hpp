#ifndef _DIJKSTRA_HPP_
#define _DIJKSTRA_HPP_

#include <vector>

namespace ACO {
    // Dijkstra's shortest path algorithm (start from nodes[start])
    std::vector<int> Dijkstra(const std::vector<std::vector<int>>& graph, int start = 0);
}

#endif // !_DIJKSTRA_HPP_