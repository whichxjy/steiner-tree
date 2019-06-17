#include "ant.hpp"
#include "common.hpp"
#include <cmath>

namespace ACO {
    // The probability to move with greedy strategy (instead of roulette strategy) in (0, 1)
    constexpr double GREEDY_PROBABILITY = 0.3;
    // The importance of pheromone when choosing the next step
    constexpr int PHM_IMP = 10;
    // The importance of weight (i.e., graph[curr_node][j]) when choosing the next step
    constexpr int WEIGHT_IMP = 4;
    // The importance of dist[j] when choosing the next step
    constexpr int DIST_IMP = 4;
}

// Constructor
ACO::Ant::Ant(int curr_node, int target_node, const std::vector<std::vector<int>>& graph,
    const std::vector<std::vector<double>>& phm, const std::vector<int>& dist)
    : curr_node(curr_node), target_node(target_node), graph(graph), phm(phm), dist(dist), visited(graph.size(), false) {
    visited[curr_node] = true;
    visited_set.insert(curr_node);
    visited_pq.emplace(dist[curr_node], curr_node);
}

// Move to the next node
void ACO::Ant::move() {
    // There are two strategies to move (i.e., state transition):
    // (1) Greedy ==> Probability: GREEDY_PROBABILITY
    // (2) Roulette ==> Probability: (1 - GREEDY_PROBABILITY)

    // The rule to calculate key for nodes[j], which determines how to choose the next node.
    auto get_key_for_node = [this](int j) -> double {
        return std::pow(phm[curr_node][j], PHM_IMP) * std::pow(graph[curr_node][j] + dist[j], -(WEIGHT_IMP + DIST_IMP));
    };

    // Where to go?
    int next_node = -1;

    // The number of all nodes
    int V = graph.size();

    if (random_real(0, 1) < GREEDY_PROBABILITY) {
        // [Greedy Strategy]: choose the node with the maximum key
        double max_key = 0;
        // Get successors of current node
        for (int j = 0; j < V; j++) {
            // If nodes[j] hadn't been visited and can be reached from current node, then calculate its key.
            if (!visited[j] && graph[curr_node][j] > 0 && get_key_for_node(j) > max_key) {
                max_key = get_key_for_node(j);
                next_node = j;
            }
        }
    }
    else {
        // [Roulette Strategy]: the probability to choose nodes[j] is (keys[j] / total_key)
        std::vector<double> keys(V);
        double total_key = 0;
        for (int j = 0; j < V; j++) {
            // keys[j] will be calculated if nodes[j] hadn't been visited and
            // can be reached from current node, if not, keys[j] = 0.
            if (!visited[j] && graph[curr_node][j] > 0) {
                keys[j] = get_key_for_node(j);
            }
            else {
                keys[j] = 0;
            }
            total_key += keys[j];
        }
        if (total_key != 0) {
            // Play roulette
            double roulette_key = random_real(0, total_key);
            for (int j = 0; j < V; j++) {
                roulette_key -= keys[j];
                if (roulette_key < 0) {
                    next_node = j;
                    break;
                }
            }
        }
    }

    if (next_node == -1) {
        // Fail to find the next node
        relocate();
    }
    else {
        // Move to next_node
        visited[next_node] = true;
        visited_set.insert(next_node);
        visited_pq.emplace(dist[next_node], next_node);
        curr_node = next_node;
    }
}

// Relocate the current node
void ACO::Ant::relocate() {
    if (!visited_pq.empty()) {
        // Get the node with the minimum dist[node] from visited nodes
        int closest = visited_pq.top().second;
        // Relocate the ant to the closest node if it's not in there
        if (curr_node == closest) {
            curr_node = target_node;
        }
        else {
            curr_node = closest;
        }
    }
}

// Check if the ant arrived the target node
bool ACO::Ant::arrived() const {
    return curr_node == target_node;
}
